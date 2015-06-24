
#include "Exceptions.h"

namespace Shh
{
	SerializeException::SerializeException(const String& desc_, const String& src_, const char* file_, long line_)
		:Exception(Exception::EXT_SERIALIZE_ERROR, desc_, src_, "SerializeException", file_, line_)
	{

	}

	FormatException::FormatException(const String& desc_, const String& src_, const char* file_, long line_)
		:Exception(Exception::EXT_FORMAT_ERROR, desc_, src_, "FormatException", file_, line_)
	{

	}

	ShaderException::ShaderException(const String& desc_, const String& src_, const char* file_, long line_)
		:Exception(Exception::EXT_SHADER_ERROR, desc_, src_, "ShaderException", file_, line_)
	{

	}

	MemoryException::MemoryException(const String& desc_, const String& src_, const char* file_, long line_)
		:Exception(Exception::EXT_MEMORY_ERROR, desc_, src_, "MemoryException", file_, line_)
	{

	}

}