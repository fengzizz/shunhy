#include "AppMouse.h"
namespace Shh
{
	AppMouse::AppMouse()
	{
	}

	AppMouse::~AppMouse()
	{

	}
	//void AppMouse::SetMousePosition(int x, int y)
	//{
	//	SetCursorPos(x, y); 
	//}

	void AppMouse::_Reset()
	{
		mMouseState.leftButton = EKS_Released;
		mMouseState.rightButton = EKS_Released;
		mMouseState.middleButton = EKS_Released;
		mMouseState.wheel = 0;
		mMouseState.x = 0;
		mMouseState.y = 0;
	}
}