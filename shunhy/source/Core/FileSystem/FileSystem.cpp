

#include <istream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

#include "StringUtility.h"
#include "Core/Convert.h"
#include "FileSystem/FileSystem.h"
//#if OGRE_PLATFORM == OGRE_PLATFORM_LINUX || OGRE_PLATFORM == OGRE_PLATFORM_APPLE || \
//	OGRE_PLATFORM == OGRE_PLATFORM_SYMBIAN || OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
//#   include "OgreSearchOps.h"
//#   include <sys/param.h>
//#   define MAX_PATH MAXPATHLEN
//#endif

#define OGRE_PLATFORM_WIN32 1//后加
#define OGRE_PLATFORM OGRE_PLATFORM_WIN32//后加

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#  define WIN32_LEAN_AND_MEAN
#  if !defined(NOMINMAX) && defined(_MSC_VER)
#	define NOMINMAX // required to stop windows.h messing up std::min
#  endif
#  include <windows.h>
//#  include <Shlwapi.h>
//#  include <direct.h>
#  include <io.h>
#endif

namespace Shh {

#define OGRE_NEW shh_new //(__FILE__, __LINE__, __FUNCTION__)
#define OGRE_DELETE shh_delete

#define OGRE_NEW_T(T, category) shh_new T
#define OGRE_ALLOC_T(T, count, category) shh_new T[count]
#define OGRE_FREE(ptr, category) shh_delete[] ptr;

#define OGRE_DELETE_T(ptr, T, category) shh_delete ptr;

	/// The method to use to free memory on destruction
	enum SharedPtrFreeMethod
	{
		/// Use OGRE_DELETE to free the memory
		SPFM_DELETE,
		/// Use OGRE_DELETE_T to free (only MEMCATEGORY_GENERAL supported)
		SPFM_DELETE_T,
		/// Use OGRE_FREE to free (only MEMCATEGORY_GENERAL supported)
		SPFM_FREE
	};

	DataStreamPtr _open_file(const String& absoluteFileName, const String& filename, bool readOnly)
	{
		// Use filesystem to determine size 
		// (quicker than streaming to the end and back)
		struct stat tagStat;
		int ret = stat(absoluteFileName.c_str(), &tagStat);
		shh_assert(ret == 0 && "Problem getting file size" );
		(void)ret;  // Silence warning

		// Always open in binary mode
		// Also, always include reading
		std::ios::openmode mode = std::ios::in | std::ios::binary;
		std::istream* baseStream = 0;
		std::ifstream* roStream = 0;
		std::fstream* rwStream = 0;

		if (readOnly)
		{
			roStream = OGRE_NEW_T(std::ifstream, MEMCATEGORY_GENERAL)();
			roStream->open(absoluteFileName.c_str(), mode);
			baseStream = roStream;
		}
		else
		{
			mode |= std::ios::out;
			rwStream = OGRE_NEW_T(std::fstream, MEMCATEGORY_GENERAL)();
			rwStream->open(absoluteFileName.c_str(), mode);
			baseStream = rwStream;
		}


		// Should check ensure open succeeded, in case fail for some reason.
		if (baseStream->fail())
		{
			OGRE_DELETE_T(roStream, basic_ifstream, MEMCATEGORY_GENERAL);
			OGRE_DELETE_T(rwStream, basic_fstream, MEMCATEGORY_GENERAL);
			shh_assert(0);
			//OGRE_EXCEPT(Exception::ERR_FILE_NOT_FOUND,
			//	"Cannot open file: " + filename,
			//	"FileSystemArchive::open");
		}

		/// Construct return stream, tell it to delete on destroy
		FileStreamDataStream* stream = 0;
		if (rwStream)
		{
			// use the writeable stream 
			stream = OGRE_NEW FileStreamDataStream(filename,
				rwStream, (size_t)tagStat.st_size, true);
		}
		else
		{
			// read-only stream
			stream = OGRE_NEW FileStreamDataStream(filename,
				roStream, (size_t)tagStat.st_size, true);
		}
		return DataStreamPtr(stream);
	}

	DataStreamPtr _create_file(const String& absoluteFileName, const String& filename)
	{
		// Always open in binary mode
		// Also, always include reading
		std::ios::openmode mode = std::ios::out | std::ios::binary;
		std::fstream* rwStream = OGRE_NEW_T(std::fstream, MEMCATEGORY_GENERAL)();
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		U16String wpath;
		utility::toUtf16(absoluteFileName, wpath);
		rwStream->open(wpath.c_str(), mode);
#else
		rwStream->open(full_path.c_str(), mode);
#endif
		// Should check ensure open succeeded, in case fail for some reason.
		if (rwStream->fail())
		{
			OGRE_DELETE_T(rwStream, basic_fstream, MEMCATEGORY_GENERAL);
			shh_assert(0);
			//OGRE_EXCEPT(Exception::ERR_FILE_NOT_FOUND,
			//	"Cannot open file: " + filename,
			//	"FileSystemArchive::create");
		}

		/// Construct return stream, tell it to delete on destroy
		FileStreamDataStream* stream = OGRE_NEW FileStreamDataStream(filename,
			rwStream, 0, true);

		return DataStreamPtr(stream);
	}

	void _remove_file(const String& absoluteFileName)
	{
		::remove(absoluteFileName.c_str());
	}

	bool _path_file_exist(const String& absoluteFileName)
	{
		struct stat tagStat;
		return (stat(absoluteFileName.c_str(), &tagStat) == 0);

	}

	void _replace(U16String& str_, U16String::value_type old_, U16String::value_type new_)
	{
		U16String::iterator it = str_.begin();
		U16String::iterator end = str_.end();
		while(it != end)
		{
			if (old_ == *it)
			{
				*it = new_;
			}
			++it;
		}
	}




	bool _create_path3(const U16String& path)
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		return TRUE == ::CreateDirectoryW((LPCWSTR)path.c_str(), NULL);
#endif
	}

	bool _create_path2(const U16String& path)
	{
		if (_create_path3(path))
		{
			return true;
		}
		else
		{
			size_t index = path.rfind('\\');
			if (U16String::npos == index)
			{
				return false;
			}
			U16String parent = path.substr(0, index);
			if(parent.empty())
			{
				return false;
			}
			else if(_create_path2(parent))
			{
				return _create_path3(path);
			}
			return false;
		}
	}

	bool _create_path(const String& path)
	{
		U16String w_path;
		utility::toUtf16(path, w_path);
		_replace(w_path, '/', '\\');
		return _create_path2(w_path);
	}
	//bool _remove_path(const String& path, bool clear)
	//{
	//	U16String w_path;
	//	Convert::utf8_to_utf16(path, w_path);
	//	_replace(w_path, '/', '\\');

	//	return _remove_path2(w_path);
	//}


	bool FileSystemArchive::ms_IgnoreHidden = true;

    //-----------------------------------------------------------------------
    FileSystemArchive::FileSystemArchive(const String& name, const String& archType )
        : Archive(name, archType)
    {
    }
    //-----------------------------------------------------------------------
    bool FileSystemArchive::isCaseSensitive(void) const
    {
        #if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            return false;
        #else
            return true;
        #endif

    }
    //-----------------------------------------------------------------------
    static bool is_reserved_dir (const char *fn)
    {
        return (fn [0] == '.' && (fn [1] == 0 || (fn [1] == '.' && fn [2] == 0)));
    }
    //-----------------------------------------------------------------------
    static bool is_absolute_path(const char* path)
    {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        if (isalpha(uchar(path[0])) && path[1] == ':')
            return true;
#endif
        return path[0] == '/' || path[0] == '\\';
    }
    //-----------------------------------------------------------------------
    static String concatenate_path(const String& base, const String& name)
    {
        if (base.empty() || is_absolute_path(name.c_str()))
            return name;
        else
            return base + '/' + name;
    }
    //-----------------------------------------------------------------------
    void FileSystemArchive::findFiles(const String& pattern, bool recursive, 
        bool dirs, StringVector* simpleList, FileInfoList* detailList)
    {
        long lHandle, res;
        struct _finddata_t tagData;

        // pattern can contain a directory name, separate it from mask
        size_t pos1 = pattern.rfind ('/');
        size_t pos2 = pattern.rfind ('\\');
        if (pos1 == pattern.npos || ((pos2 != pattern.npos) && (pos1 < pos2)))
            pos1 = pos2;
        String directory;
        if (pos1 != pattern.npos)
            directory = pattern.substr (0, pos1 + 1);

        String full_pattern = getFullPath(pattern);

        lHandle = _findfirst(full_pattern.c_str(), &tagData);
        res = 0;
        while (lHandle != -1 && res != -1)
        {
            if ((dirs == ((tagData.attrib & _A_SUBDIR) != 0)) &&
				( !ms_IgnoreHidden || (tagData.attrib & _A_HIDDEN) == 0 ) &&
                (!dirs || !is_reserved_dir (tagData.name)))
            {
                if (simpleList)
                {
                    simpleList->push_back(directory + tagData.name);
                }
                else if (detailList)
                {
                    FileInfo fi;
                    fi.archive = this;
                    fi.filename = directory + tagData.name;
                    fi.basename = tagData.name;
                    fi.path = directory;
                    fi.compressedSize = tagData.size;
                    fi.uncompressedSize = tagData.size;
                    detailList->push_back(fi);
                }
            }
            res = _findnext( lHandle, &tagData );
        }
        // Close if we found any files
        if(lHandle != -1)
            _findclose(lHandle);

        // Now find directories
        if (recursive)
        {
            String base_dir = mName;
            if (!directory.empty ())
            {
                base_dir = getFullPath(directory);
                // Remove the last '/'
                base_dir.erase (base_dir.length () - 1);
            }
            base_dir.append ("/*");

            // Remove directory name from pattern
            String mask ("/");
            if (pos1 != pattern.npos)
                mask.append (pattern.substr (pos1 + 1));
            else
                mask.append (pattern);

            lHandle = _findfirst(base_dir.c_str (), &tagData);
            res = 0;
            while (lHandle != -1 && res != -1)
            {
                if ((tagData.attrib & _A_SUBDIR) &&
					( !ms_IgnoreHidden || (tagData.attrib & _A_HIDDEN) == 0 ) &&
                    !is_reserved_dir (tagData.name))
                {
                    // recurse
                    base_dir = directory;
                    base_dir.append (tagData.name).append (mask);
                    findFiles(base_dir, recursive, dirs, simpleList, detailList);
                }
                res = _findnext( lHandle, &tagData );
            }
            // Close if we found any files
            if(lHandle != -1)
                _findclose(lHandle);
        }
    }
    //-----------------------------------------------------------------------
    FileSystemArchive::~FileSystemArchive()
    {
        unload();
    }
    //-----------------------------------------------------------------------
    void FileSystemArchive::load()
    {
		//OGRE_LOCK_AUTO_MUTEX
  //      // test to see if this folder is writeable
		//String testPath = getFullPath("__testwrite.ogre");
		//std::ofstream writeStream;
		//writeStream.open(testPath.c_str());
		//if (writeStream.fail())
		//	mReadOnly = true;
		//else
		//{
		//	mReadOnly = false;
		//	writeStream.close();
		//	::remove(testPath.c_str());
		//}
    }
    //-----------------------------------------------------------------------
    void FileSystemArchive::unload()
    {
        // nothing to see here, move along
    }
    //-----------------------------------------------------------------------
    DataStreamPtr FileSystemArchive::open(const String& filename, bool readOnly) const
    {
		String full_path = getFullPath(filename);

		return _open_file(full_path, filename, readOnly || isReadOnly());
    }
	//---------------------------------------------------------------------
	DataStreamPtr FileSystemArchive::createFile(const String& filename) const
	{
		if (isReadOnly())
		{
			shh_assert(0);
			//OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, 
			//	"Cannot create a file in a read-only archive", 
			//	"FileSystemArchive::remove");
		}

		String full_path = getFullPath(filename);

		return _create_file(full_path, filename);
	}
	//---------------------------------------------------------------------
	void FileSystemArchive::createPath(const String& path) const
	{
		String full_path = getFullPath(path);
		_create_path(full_path);
	}
	//---------------------------------------------------------------------
	//---------------------------------------------------------------------
	void FileSystemArchive::removeFile(const String& filename) const
	{
		if (isReadOnly())
		{
			shh_assert(0);
			//OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, 
			//	"Cannot remove a file from a read-only archive", 
			//	"FileSystemArchive::remove");
		}
		String full_path = getFullPath(filename);
		::remove(full_path.c_str());

	}
    //-----------------------------------------------------------------------
    StringVectorPtr FileSystemArchive::list(bool recursive, bool dirs)
    {
		// directory change requires locking due to saved returns
		// Note that we have to tell the SharedPtr to use OGRE_DELETE_T not OGRE_DELETE by passing category
		StringVectorPtr ret(OGRE_NEW_T(StringVector, MEMCATEGORY_GENERAL)());//, SPFM_DELETE_T);

        //findFiles("*", recursive, dirs, ret.getPointer(), 0);
		findFiles("*", recursive, dirs, ret.get(), 0);
        return ret;
    }
    //-----------------------------------------------------------------------
    FileInfoListPtr FileSystemArchive::listFileInfo(bool recursive, bool dirs)
    {
		// Note that we have to tell the SharedPtr to use OGRE_DELETE_T not OGRE_DELETE by passing category
        FileInfoListPtr ret(OGRE_NEW_T(FileInfoList, MEMCATEGORY_GENERAL)());//, , SPFM_DELETE_T);

        //findFiles("*", recursive, dirs, 0, ret.getPointer());
		findFiles("*", recursive, dirs, 0, ret.get());

        return ret;
    }
    //-----------------------------------------------------------------------
    StringVectorPtr FileSystemArchive::find(const String& pattern,
                                            bool recursive, bool dirs)
    {
		// Note that we have to tell the SharedPtr to use OGRE_DELETE_T not OGRE_DELETE by passing category
		StringVectorPtr ret(OGRE_NEW_T(StringVector, MEMCATEGORY_GENERAL)());//, , SPFM_DELETE_T);

        //findFiles(pattern, recursive, dirs, ret.getPointer(), 0);
		findFiles(pattern, recursive, dirs, ret.get(), 0);

        return ret;

    }
    //-----------------------------------------------------------------------
    FileInfoListPtr FileSystemArchive::findFileInfo(const String& pattern, 
        bool recursive, bool dirs)
    {
		// Note that we have to tell the SharedPtr to use OGRE_DELETE_T not OGRE_DELETE by passing category
		FileInfoListPtr ret(OGRE_NEW_T(FileInfoList, MEMCATEGORY_GENERAL)());//, , SPFM_DELETE_T);

        //findFiles(pattern, recursive, dirs, 0, ret.getPointer());
		findFiles(pattern, recursive, dirs, 0, ret.get());

        return ret;
    }
    //-----------------------------------------------------------------------
	bool FileSystemArchive::exists(const String& filename)
	{
        String full_path = getFullPath(filename);

        struct stat tagStat;
        bool ret = (stat(full_path.c_str(), &tagStat) == 0);

		// stat will return true if the filename is absolute, but we need to check
		// the file is actually in this archive
        if (ret && is_absolute_path(filename.c_str()))
		{
			// only valid if full path starts with our base
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			// case insensitive on windows
			String lowerCaseName = mName;
			utility::toLowerCase(lowerCaseName);
			ret = utility::startsWith(full_path, lowerCaseName, true);
#else
			// case sensitive
			ret = utility::startsWith(full_path, mName, false);
#endif
		}

		return ret;
	}
	//---------------------------------------------------------------------
	time_t FileSystemArchive::getModifiedTime(const String& filename)
	{
		String full_path = getFullPath(filename);

		struct stat tagStat;
		bool ret = (stat(full_path.c_str(), &tagStat) == 0);

		if (ret)
		{
			return tagStat.st_mtime;
		}
		else
		{
			return 0;
		}

	}

}