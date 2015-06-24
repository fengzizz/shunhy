#ifndef __INPUTLISTENER_H__
#define __INPUTLISTENER_H__
#include "AppDef.h"
#include "InputEvent.h"
namespace Shh
{


	class _Shh_Export InputListener
	{
	public:	
		enum Priority
		{
			GUI = 0,
			System = 0x88,
			Lowest,
			Max = 0xff,
		};
		virtual ~InputListener()
		{
	
		}
		// 鼠标、键盘事件
		virtual bool SetKeyEvent(EKeys key, EKeyState state) = 0; // 键盘事件
		virtual bool SetMouseEvent(EKeys key, EKeyState state, int x, int y) = 0;//鼠标事件
		virtual bool SetMouseMove( int x, int y) = 0;//鼠标事件
		virtual bool AddWheel(int roll) = 0;//鼠标事件		
		//非鼠标、键盘事件
		virtual bool SetButton(EKeys key, EKeyState state) = 0;	//手柄？。
		virtual Priority GetPriority() const = 0;
	};
}
#endif //__INPUTLISTENER_H__