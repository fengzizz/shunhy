#ifndef __APP_INPUTEVENT_H__
#define __APP_INPUTEVENT_H__
#include "AppDef.h"

namespace Shh
{
	enum EKeyState
	{
		EKS_Released,
		EKS_Pressed
	};
	enum EKeys
	{
		EKey_A = 0x41,
		EKey_Add = 0x6b,
		EKey_Apps = 0x5d,
		EKey_Attn = 0xf6,
		EKey_B = 0x42,
		EKey_Back = 8,
		EKey_BrowserBack = 0xa6,
		EKey_BrowserFavorites = 0xab,
		EKey_BrowserForward = 0xa7,
		EKey_BrowserHome = 0xac,
		EKey_EKey_BrowserRefresh = 0xa8,
		EKey_BrowserSearch = 170,
		EKey_BrowserStop = 0xa9,
		EKey_C = 0x43,
		EKey_CapsLock = 20,
		EKey_ChatPadGreen = 0xca,
		EKey_ChatPadOrange = 0xcb,
		EKey_Crsel = 0xf7,
		EKey_D = 0x44,
		EKey_D0 = 0x30,
		EKey_D1 = 0x31,
		EKey_D2 = 50,
		EKey_D3 = 0x33,
		EKey_D4 = 0x34,
		EKey_D5 = 0x35,
		EKey_D6 = 0x36,
		EKey_D7 = 0x37,
		EKey_D8 = 0x38,
		EKey_D9 = 0x39,
		EKey_Decimal = 110,
		EKey_Delete = 0x2e,
		EKey_Divide = 0x6f,
		EKey_Down = 40,
		EKey_E = 0x45,
		EKey_End = 0x23,
		EKey_Enter = 13,
		EKey_EraseEof = 0xf9,
		EKey_Escape = 0x1b,
		EKey_Execute = 0x2b,
		EKey_Exsel = 0xf8,
		EKey_F = 70,
		EKey_F1 = 0x70,
		EKey_F10 = 0x79,
		EKey_F11 = 0x7a,
		EKey_F12 = 0x7b,
		EKey_F13 = 0x7c,
		EKey_F14 = 0x7d,
		EKey_F15 = 0x7e,
		EKey_F16 = 0x7f,
		EKey_F17 = 0x80,
		EKey_F18 = 0x81,
		EKey_F19 = 130,
		EKey_F2 = 0x71,
		EKey_F20 = 0x83,
		EKey_F21 = 0x84,
		EKey_F22 = 0x85,
		EKey_F23 = 0x86,
		EKey_F24 = 0x87,
		EKey_F3 = 0x72,
		EKey_F4 = 0x73,
		EKey_F5 = 0x74,
		EKey_F6 = 0x75,
		EKey_F7 = 0x76,
		EKey_F8 = 0x77,
		EKey_F9 = 120,
		EKey_G = 0x47,
		EKey_H = 0x48,
		EKey_Help = 0x2f,
		EKey_Home = 0x24,
		EKey_I = 0x49,
		EKey_ImeConvert = 0x1c,
		EKey_ImeNoConvert = 0x1d,
		EKey_Insert = 0x2d,
		EKey_J = 0x4a,
		EKey_K = 0x4b,
		EKey_Kana = 0x15,
		EKey_Kanji = 0x19,
		EKey_L = 0x4c,
		EKey_LaunchApplication1 = 0xb6,
		EKey_LaunchApplication2 = 0xb7,
		EKey_LaunchMail = 180,
		EKey_Left = 0x25,
		EKey_LeftAlt = 0xa4,
		EKey_LeftControl = 0xa2,
		EKey_LeftShift = 160,
		EKey_LeftWindows = 0x5b,
		EKey_M = 0x4d,
		EKey_MediaNextTrack = 0xb0,
		EKey_MediaPlayPause = 0xb3,
		EKey_MediaPreviousTrack = 0xb1,
		EKey_MediaStop = 0xb2,
		EKey_Multiply = 0x6a,
		EKey_N = 0x4e,
		EKey_None = 0,
		EKey_NumLock = 0x90,
		EKey_NumPad0 = 0x60,
		EKey_NumPad1 = 0x61,
		EKey_NumPad2 = 0x62,
		EKey_NumPad3 = 0x63,
		EKey_NumPad4 = 100,
		EKey_NumPad5 = 0x65,
		EKey_NumPad6 = 0x66,
		EKey_NumPad7 = 0x67,
		EKey_NumPad8 = 0x68,
		EKey_NumPad9 = 0x69,
		EKey_O = 0x4f,
		EKey_Oem8 = 0xdf,
		EKey_OemAuto = 0xf3,
		EKey_OemBackslash = 0xe2,
		EKey_OemClear = 0xfe,
		EKey_OemCloseBrackets = 0xdd,
		EKey_OemComma = 0xbc,
		EKey_OemCopy = 0xf2,
		EKey_OemEnlW = 0xf4,
		EKey_OemMinus = 0xbd,
		EKey_OemOpenBrackets = 0xdb,
		EKey_OemPeriod = 190,
		EKey_OemPipe = 220,
		EKey_OemPlus = 0xbb,
		EKey_OemQuestion = 0xbf,
		EKey_OemQuotes = 0xde,
		EKey_OemSemicolon = 0xba,
		EKey_OemTilde = 0xc0,
		EKey_P = 80,
		EKey_Pa1 = 0xfd,
		EKey_PageDown = 0x22,
		EKey_PageUp = 0x21,
		EKey_Pause = 0x13,
		EKey_Play = 250,
		EKey_Print = 0x2a,
		EKey_PrintScreen = 0x2c,
		EKey_ProcessKey = 0xe5,
		EKey_Q = 0x51,
		EKey_R = 0x52,
		EKey_Right = 0x27,
		EKey_RightAlt = 0xa5,
		EKey_RightControl = 0xa3,
		EKey_RightShift = 0xa1,
		EKey_RightWindows = 0x5c,
		EKey_S = 0x53,
		EKey_Scroll = 0x91,
		EKey_Select = 0x29,
		EKey_SelectMedia = 0xb5,
		EKey_Separator = 0x6c,
		EKey_Sleep = 0x5f,
		EKey_Space = 0x20,
		EKey_Subtract = 0x6d,
		EKey_T = 0x54,
		EKey_Tab = 9,
		EKey_U = 0x55,
		EKey_Up = 0x26,
		EKey_V = 0x56,
		EKey_VolumeDown = 0xae,
		EKey_VolumeMute = 0xad,
		EKey_VolumeUp = 0xaf,
		EKey_W = 0x57,
		EKey_X = 0x58,
		EKey_Y = 0x59,
		EKey_Z = 90,
		EKey_Zoom = 0xfb,

		EKey_Shift = 0x10,		//左右不分
		EKey_Control = 0x11,	//左右不分
		EKey_Alt = 0x12,		//左右不分

		

		//键盘之外的输入事件	
		EBS_MouseL = 0x100,
		EBS_MouseR,
		EBS_MouseM,

		EBS_ButtonA,//手柄什么的。
		EBS_Max = 0xffff //16位无符号最大值
	};


	class InputEvent //高16位为按键枚举，低16位为自定义值，如按下状态等
	{
	public:
		InputEvent(EKeys key, uint16 value);
	private:
		uint16 mKey;
		uint16 mValue;
	};
	inline InputEvent::InputEvent(EKeys key, uint16 value)
		:mKey(key)
		,mValue(value)
	{
	}
}

#endif //__APP_INPUTEVENT_H__