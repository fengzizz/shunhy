#ifndef __DEBUGWIN32_H__
#define __DEBUGWIN32_H__

#include <Windows.h>

typedef wchar_t Win32Char16;
#define _WIN32_DEBUG_OUTPUTA(x) OutputDebugStringA(x)
#define _WIN32_DEBUG_OUTPUTW(x) OutputDebugStringW(x)
#endif