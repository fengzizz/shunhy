#ifndef __APPMOUSE_H__
#define __APPMOUSE_H__
#include "Mouse.h"
namespace Shh
{
	class AppMouse : public Mouse
	{
	public:
		AppMouse();
		~AppMouse();
		//void SetMousePosition(int x, int y)
		void _Reset();
		void _SetLButtonState(EKeyState state);
		void _SetRButtonState(EKeyState state);
		void _SetMButtonState(EKeyState state);
		void _SetMousePos(int x, int y);
		void _SetWheel(int roll);		
		void _AddWheel(int roll);		
		void _ResetWheel();
	};

	inline void AppMouse::_SetLButtonState(EKeyState state)
	{
		mMouseState.leftButton = state;
	}
	inline void AppMouse::_SetRButtonState(EKeyState state)
	{
		mMouseState.rightButton = state;
	}
	inline void AppMouse::_SetMButtonState(EKeyState state)
	{
		mMouseState.middleButton = state;
	}
	inline void AppMouse::_SetMousePos(int x, int y)
	{
		mMouseState.x = x;
		mMouseState.y = y;
	}
	inline void AppMouse::_SetWheel(int roll)
	{
		mMouseState.wheel = roll;
	}
	inline void AppMouse::_AddWheel(int roll)
	{
		mMouseState.wheel += roll;
	}
	inline void AppMouse::_ResetWheel()
	{
		mMouseState.wheel = 0;
	}
}

#endif //__APPMOUSE_H__