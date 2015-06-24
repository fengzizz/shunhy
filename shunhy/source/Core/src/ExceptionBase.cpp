#include "StringUtility.h"
#include "ExceptionBase.h"

namespace Shh
{
	Exception::~Exception() throw()
	{

	}

	Exception::Exception(const String& description_, const String& source_)
	:line(0)
	,type(EXT_UNDEF_TYPE)
	,title("Exception")
	,description(description_)
	,source(source_)
	{
		// Log this error - not any more, allow catchers to do it
		//LogManager::getSingleton().logMessage(this->getFullDescription());
	}

	Exception::Exception(const String& description_, const String& source_, const char* file_, long line_)
		:type(EXT_UNDEF_TYPE)
		,title("Exception")
		,description(description_)
		,source(source_)
		,file(file_)
		,line(line_)
		
	{
		// Log this error - not any more, allow catchers to do it
		//LogManager::getSingleton().logMessage(this->getFullDescription());
	}

	Exception::Exception(int type_, const String& description_, const String& source_, const char* tile_, const char* file_, long line_)
		:line(line_)
		,type(type_)
		,title(tile_)
		,description(description_)
		,source(source_)
		,file(file_)
	{

	}

	Exception::Exception(const Exception& rhs)
		: line(rhs.line), 
		type(rhs.type), 
		title(rhs.title), 
		description(rhs.description), 
		source(rhs.source), 
		file(rhs.file)
	{
	}

	void Exception::operator = (const Exception& rhs)
	{
		description = rhs.description;
		type = rhs.type;
		source = rhs.source;
		file = rhs.file;
		line = rhs.line;
		title = rhs.title;
	}

    const String& Exception::GetFullDescription() const
	{
		if (0 == fullDesc.size())
		{	
			if( line > 0 )
			{
				utility::format(fullDesc, "SHH EXCEPTION(%d:%s): \"%s\" in %s at %s(line, %d)", 
					type, title.c_str(), description.c_str(), source.c_str(), file.c_str(), line);
			}
			else
			{
				utility::format(fullDesc, "SHH EXCEPTION(%d:%s): \"%s\" in %s", type, title.c_str(), description.c_str(), source.c_str());
			}
		}

		return fullDesc;
	}

    int Exception::GetType(void) const throw()
	{
		return type;
	}

    const String &Exception::GetSource() const 
	{ 
		return source;
	}

    const String &Exception::GetFile() const 
	{ 
		return file; 
	}

    long Exception::GetLine() const 
	{ 
		return line; 
	}

	const String &Exception::GetDescription(void) const 
	{ 
		return description; 
	}

	const char* Exception::what() const throw() 
	{ 
		return GetFullDescription().c_str(); 
	}
}