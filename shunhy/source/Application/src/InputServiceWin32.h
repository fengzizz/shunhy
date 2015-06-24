#ifndef __INPUTSERVICEWIN32_H__
#define __INPUTSERVICEWIN32_H__
#include <Windows.h>
#include "PrivateDef.h"
#include "InputServiceBase.h"
namespace Shh
{
	//typedef delegates::CDelegate0 EventHandle_Exit;
	class InputServerWin32 : public InputServerBase<InputServerWin32>
	{
		__Dynamic_Alloc(InputServerWin32)
	public:
		InputServerWin32();
		~InputServerWin32();
		void Start();
		bool Tick();
		bool CheckExitEvent();

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);//
	private:
		LRESULT _input(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		MSG	mMsg;
	};

	inline bool InputServerWin32::CheckExitEvent()
	{
		return (mMsg.message ==  WM_QUIT);
	}
}

#endif //__INPUTSERVICEWIN32_H__
