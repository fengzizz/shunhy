
#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__
#include "Core/ExceptionBase.h"

namespace Shh
{

#define SHH_EXCEPT(Type, desc, src) throw Type(desc, src, __FILE__, __LINE__)

	class _Shh_Export SerializeException : public Exception
	{
	public:
		SerializeException(const String& desc_, const String& src_, const char* file_, long line_);
	};

	class _Shh_Export FormatException : public Exception
	{
	public:
		FormatException(const String& desc_, const String& src_, const char* file_, long line_);
	};

	class _Shh_Export ShaderException : public Exception
	{
	public:
		ShaderException(const String& desc_, const String& src_, const char* file_, long line_);
	};

	class _Shh_Export MemoryException : public Exception
	{
	public:
		MemoryException(const String& desc_, const String& src_, const char* file_, long line_);
	};
}
#endif //__EXCEPTIONS_H__