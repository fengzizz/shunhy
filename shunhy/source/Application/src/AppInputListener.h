#ifndef __APPINPUTLISTENER_H__
#define __APPINPUTLISTENER_H__
#include "PrivateDef.h"
#include "InputListener.h"

#include "AppKeyboard.h"
#include "AppMouse.h"
namespace Shh
{

	class AppInputListener : public InputListener
	{
		__Dynamic_Alloc(AppInputListener);
	public:
		AppInputListener();
		~AppInputListener();

		virtual bool SetKeyEvent(EKeys key, EKeyState state) override;
		virtual bool SetMouseEvent(EKeys key, EKeyState state, int x, int y) override;
		virtual bool SetMouseMove( int x, int y) override;
		virtual bool AddWheel(int roll) override;

		virtual bool SetButton(EKeys key, EKeyState state) override;
		virtual InputListener::Priority GetPriority() const;

		Keyboard& GetKeyboard();
		Mouse& GetMouse();
	private: 
		AppKeyboard mKeyboard;
		AppMouse mMouse;
	};

	inline Keyboard& AppInputListener::GetKeyboard()
	{
		return mKeyboard;
	}

	inline Mouse& AppInputListener::GetMouse()
	{
		return mMouse;
	}

}
#endif