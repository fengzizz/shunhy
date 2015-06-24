#ifndef __WINCONFIG_H__
#define __WINCONFIG_H__


//#define SafeRelease(x) if (NULL != x) { x->Release(); }

#ifdef SHANHAIWIN_EXPORTS
#define SHH_WIN_API __declspec(dllexport)
#else
#define SHH_WIN_API __declspec(dllimport)
#endif

#define SHHCALLCONV __cdecl
#include "Debug.h"

namespace Shh
{
	class IKeyboard;
	class IMouse;
	class GameTime;
}
#endif //__WINCONFIG_H__
