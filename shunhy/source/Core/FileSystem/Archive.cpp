#include "Core/StringUtility.h"
#include "Core/Log.h"
#include "FileSystem/Archive.h"

namespace Shh
{

	static String Colon = ":";
	static String Slash = "/";

	/** Constructor - don't call direct, used by ArchiveFactory.
    */
    Archive::Archive( const String& name, const String& archType )
        : mName(name), mType(archType), mReadOnly(false) 
	{

	}

    /** Default destructor.
    */
    Archive::~Archive() 
	{
	}

	/// Get the name of this archive
	const String& Archive::getName(void) const 
	{ 
		return mName; 
	}

	DataStreamPtr Archive::create(const String& filename) const
	{
		(void)filename;
		shh_error("This archive does not support creation of files: Archive::create");
/*		OGRE_EXCEPT(Exception::ERR_NOT_IMPLEMENTED, 
			"This archive does not support creation of files.", 
			"Archive::create")*/;
		return nullptr;
	}

	/** Delete a named file.
	@remarks Not possible on read-only archives
	@param filename The fully qualified name of the file
	*/
	void Archive::remove(const String& filename) const
	{
        (void)filename;
		shh_error("This archive does not support removal of files: Archive::remove");
		//OGRE_EXCEPT(Exception::ERR_NOT_IMPLEMENTED, 
		//	"This archive does not support removal of files.", 
		//	"Archive::remove");
	}

    /// Return the type code of this Archive
    const String& Archive::getType(void) const 
	{ 
		return mType; 
	}


	PathAssign& Archive::GetAssign()
	{
		return mAssign;
	}

	String Archive::getFullPath(const String& name) const
	{
		StringVector split;
		utility::split(split, name, Colon, 2);

		if (PathAssign::FullKey == split[0])
		{
			return split[1];
		}
		const String& sub = mAssign.Get(split[0]);
		String full = mName;
		if (sub.size() > 0)
		{
			full += Slash + sub;
		}
		if (split.size() > 1)
		{
			full += Slash + split[1];
		}
		
		return full;
	}
}