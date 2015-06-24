#pragma once
#include <Windows.h>
#include "ShhMouse.h"

namespace Shh
{
	ShhMouse::ShhMouse()
	{

	}
	ShhMouse::~ShhMouse()
	{
	}
	void ShhMouse::SetMousePosition(int x, int y)
	{
		SetCursorPos(x, y); 
	}
	MouseState ShhMouse::GetMouseState()
	{
		return mMouseState;
	}
}