#pragma once
#include "WinConfig.h"
namespace Shh
{

	enum EShhButtonState
	{
		EShhBS_Released,
		EShhBS_Pressed
	};

	class ShhMouseState//SHH_WIN_API
	{
	public:
		inline ShhMouseState():
		x(0),y(0),wheel(0),leftButton(EShhBS_Released),rightButton(EShhBS_Released),middleButton(EShhBS_Released)
		{

		}		
		int x;
		int y;
		int wheel;
		EShhButtonState leftButton;
		EShhButtonState rightButton;
		EShhButtonState middleButton;
		
	};
	typedef ShhMouseState MouseState;

	class IMouse
	{
	public:
		virtual ~IMouse(){}
		virtual MouseState GetMouseState() = 0;
		virtual void SetMousePosition(int x, int y) = 0;
 	};

}

