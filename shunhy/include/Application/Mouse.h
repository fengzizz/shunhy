#ifndef __APP_MOUSE_H__
#define __APP_MOUSE_H__
#include "InputEvent.h"
namespace Shh
{
	class _Shh_Export MouseState//SHH_WIN_API
	{
	public:
		inline MouseState():
		x(0),y(0),wheel(0),leftButton(EKS_Released),rightButton(EKS_Released),middleButton(EKS_Released)
		{

		}		
		int x;
		int y;
		int wheel;
		EKeyState leftButton;
		EKeyState rightButton;
		EKeyState middleButton;

	};

	class _Shh_Export Mouse
	{
	public:

		~Mouse();
		const MouseState& GetMouseState() const;
		//void SetMousePosition(int x, int y);
	protected:		
		Mouse();
		MouseState mMouseState;
	};
}
#endif //__APP_MOUSE_H__