#ifndef __LOG_H__
#define __LOG_H__
#include <sstream>
#include "Core/TEnum.h"
#include "Core/U8String.h"
#include "Core/Exceptions.h"
namespace Shh
{
	class LogLevel
	{
		__Declare_Enum
		{
			Info = 0,
			Warnning = 100,
			Error = 200,
		};
		__Declare_Enum_Struct(LogLevel,0);
	};

	U8String _Shh_Export _GetLogFileName();

	void _Shh_Export _Message(LogLevel level, const String& msg);

	void _Shh_Export _Message(LogLevel level, const std::stringstream& sstream);

	void _Shh_Export _Message(LogLevel level, const char* format, ...);

	void _Shh_Export __shh_error(const char* file, long line, const char* format, ...);

	void __set_logfilename(const U8String& name);

#define shh_warnning(fmt, ...) Shh::_Message(Shh::LogLevel(Shh::LogLevel::Warnning), fmt, __VA_ARGS__)

#define shh_log(fmt, ...) Shh::_Message(Shh::LogLevel(Shh::LogLevel::Info), fmt, __VA_ARGS__)

#define shh_error(fmt, ...) Shh::__shh_error(__FILE__, __LINE__, fmt, __VA_ARGS__)


#define shh_sstream_log(lvl, _stream) shh_log(lvl, _stream.str().c_str())

#define SSTREAM_COUT(ssname) std::stringstream ssname; ssname

}

#endif //__LOG_H__

