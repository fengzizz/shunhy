#include "Convert.h"
#include "Log.h"
#include "FileSystem/FileSystem.h"
#include <cstdarg>


namespace Shh
{
	static DataStreamPtr LogFileStream;
	static const String LineCode = "\r\n";

	static String LogFileName;// = "home:game.log";
	static const String StringLog = "log: ";
	static const String StringWarning = "warning: ";
	static const String StringError = "error:";

	void __set_logfilename(const U8String& name)
	{
		LogFileName = name;
	}

	U8String _GetLogFileName()
	{
		return LogFileName;
	}

	void _message(const String& msg)
	{
		if (LogFileStream.use_count() == 0)
		{
			if (LogFileName.size() == 0)
			{
				return;
			}
			bool exist = _path_file_exist(LogFileName);
			if (exist)
			{
				_remove_file(LogFileName);
			}
			LogFileStream = _create_file(LogFileName, LogFileName);

			//LogFileStream = _open_file(LogFileName, LogFileName, false);

			LogFileStream->seek(LogFileStream->size());

			char head[3] = {(char)U8HEAD0, (char)U8HEAD1, (char)U8HEAD2};// utf8 head
			LogFileStream->write(head, 3);

			U8String hello = "log system init.\r\n";
			LogFileStream->write(hello.c_str(), hello.size());

			LogFileStream->write(msg.c_str(), msg.size());
			LogFileStream->flush();
		}
		else
		{
			LogFileStream->write(msg.c_str(), msg.size());
			LogFileStream->flush();
		}

	}

	void _Message(LogLevel level, const String& msg)
	{
		U8String u8; 
		switch(level.getEnum())
		{
		case LogLevel::Info:
			{
				u8 = StringLog;
				break;
			}
		case LogLevel::Warnning:
			{
				u8 = StringWarning;
				break;
			}
		case LogLevel::Error:
			{
				u8 = StringError;
				break;
			}
		default:
			{
				break;
			}
		}

		u8 += msg;
		u8 += LineCode;
		_DebugOutput(u8.c_str());
		_message(u8);
	}


	void _Message(LogLevel level, const std::stringstream& sstream)
	{
		_Message(level, sstream.str());
	}

	void _Message(LogLevel level, const char* format, ...)
	{
		char msg[1024] = {0};
		va_list arg_ptr;
		va_start(arg_ptr, format);
		int nWrittenBytes = vsprintf_s(msg, 1024, format, arg_ptr);
		va_end(arg_ptr);

		U8String u8 = msg;
		_Message(level, u8);
	}


	void __shh_error(const char* file, long line, const char* format, ...)
	{
		char msg[1024] = {0};
		va_list arg_ptr;
		va_start(arg_ptr, format);
		int nWrittenBytes = vsprintf_s(msg, 1024, format, arg_ptr);
		va_end(arg_ptr);
		U8String u8 = msg;
		_Message(LogLevel::Error, u8);

		throw Exception("error", msg, file, line);
	}
}