#ifndef __APPKEYBOARD_H__
#define __APPKEYBOARD_H__
#include "AppDef.h"
#include "PrivateDef.h"
#include "Keyboard.h"
namespace Shh
{
	class AppKeyboard : public Keyboard
	{
	public:
		AppKeyboard();
		~AppKeyboard();
		void _SetKeyPress(EKeys key);
		void _SetKeyUp(EKeys key);
		void _Reset();
	};
}

#endif //__APPKEYBOARD_H__