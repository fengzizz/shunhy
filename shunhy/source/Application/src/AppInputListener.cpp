#include "AppInputListener.h"

namespace Shh
{
	AppInputListener::AppInputListener()
	{

	}
	AppInputListener::~AppInputListener()
	{

	}
	bool AppInputListener::SetKeyEvent(EKeys key, EKeyState state)
	{
		if (EKS_Pressed == state)
		{
			mKeyboard._SetKeyPress(key);
		}
		else
		{
			mKeyboard._SetKeyUp(key);
		}
		return false;
	}

	bool AppInputListener::SetMouseEvent(EKeys key, EKeyState state, int x, int y)
	{
		switch(key)
		{
		case EBS_MouseL:
			{
				mMouse._SetLButtonState(state);
				break;
			}
		case EBS_MouseR:
			{
				mMouse._SetRButtonState(state);
				break;
			}
		case EBS_MouseM:
			{
				mMouse._SetMButtonState(state);
				break;
			}
		default:
			break;
		}
		mMouse._SetMousePos(x, y);
		return false;
	}

	bool AppInputListener::SetMouseMove( int x, int y)
	{
		mMouse._SetMousePos(x,y);
		return false;
	}
	bool AppInputListener::AddWheel(int roll)
	{
		return false;
	}
	bool AppInputListener::SetButton(EKeys key, EKeyState state)
	{
		return false;
	}

	InputListener::Priority AppInputListener::GetPriority() const
	{
		return InputListener::System;
	}
	
}