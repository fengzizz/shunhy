#include "Convert.h"
#include "Log.h"
#include "Debug.h"

#if _Shh_Platform == _Shh_Platform_Windows
#	include "DebugWin32.h"
#   pragma warning (disable : 4996)
#   pragma warning (disable : 4717)
#endif // _DEBUG


#if _Shh_Platform == _Shh_Platform_Windows
typedef  Win32Char16 CHAR16_T;
#define  _DEBUG_OUTPUTA(x) _WIN32_DEBUG_OUTPUTA(x)
#define  _DEBUG_OUTPUTW(x) _WIN32_DEBUG_OUTPUTW(x)

#endif // WIN32


namespace Shh
{

#if _Shh_Platform == _Shh_Platform_Windows
	static const wchar_t line_code_w[] = L"\n";
#endif

	void _DebugOutput(const char* ouput)
	{
		U16String u16;
		utility::toUtf16(ouput, u16);
		_DEBUG_OUTPUTW((CHAR16_T*)u16.c_str());
	}

	void _DebugOutputLine(const char* ouput)
	{
		_DebugOutput(ouput);
		_DEBUG_OUTPUTW(line_code_w);
	}

}