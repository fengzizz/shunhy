#pragma once

#include "Mouses.h"

namespace Shh
{
	class ShhMouse : public IMouse
	{
	public:
		ShhMouse();
		~ShhMouse();
		virtual MouseState GetMouseState();
		virtual void SetMousePosition(int x, int y);
		void Present();
		void Reset();
		void SetLButtonState(EShhButtonState state);
		void SetRButtonState(EShhButtonState state);
		void SetMButtonState(EShhButtonState state);
		void SetMousePos(int x, int y);
		void SetWheel(int roll);
		void AddWheel(int roll);
		void ResetWheel();
	private:
		MouseState mMouseState;
	};
	inline void ShhMouse::Reset()
	{
		mMouseState.leftButton = EShhBS_Released;
		mMouseState.rightButton = EShhBS_Released;
		mMouseState.middleButton = EShhBS_Released;
		mMouseState.wheel = 0;
		mMouseState.x = 0;
		mMouseState.y = 0;
	}
	inline void ShhMouse::SetLButtonState(EShhButtonState state)
	{
		mMouseState.leftButton = state;
	}
	inline void ShhMouse::SetRButtonState(EShhButtonState state)
	{
		mMouseState.rightButton = state;
	}
	inline void ShhMouse::SetMButtonState(EShhButtonState state)
	{
		mMouseState.middleButton = state;
	}
	inline void ShhMouse::SetMousePos(int x, int y)
	{
		mMouseState.x = x;
		mMouseState.y = y;
	}
	inline void ShhMouse::SetWheel(int roll)
	{
		mMouseState.wheel = roll;
	}
	inline void ShhMouse::AddWheel(int roll)
	{
		mMouseState.wheel += roll;
	}
	inline void ShhMouse::ResetWheel()
	{
		mMouseState.wheel = 0;
	}

	inline void ShhMouse::Present()
	{
		ResetWheel();
	}
}