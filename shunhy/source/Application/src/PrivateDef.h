#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "Core/CoreDef.h"
#include "Core/Debug.h"
namespace Shh
{


	class AppInputListener;
	class GameService;
	class AppKeyboard;
	class AppMouse;
	
#ifdef WIN32
	class InputServerWin32;
	typedef InputServerWin32 InputService;

	class DisplayWin32;
	typedef DisplayWin32 Display;
#endif
}




#endif //__CONFIG_H__