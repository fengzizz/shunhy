

#ifndef shWindow_H
#define shWindow_H

#include <Windows.h>
#include <string>
#include <vector>

#include "IWindow.h"
#include "Keyboard.h"
#include "ShhWinCommDef.h"

namespace Shh
{
	class RenderDriver;
	class ShhWindow : public IWindow//SHH_WIN_API
	{
	public:
		ShhWindow(HINSTANCE hInstance, wchar_t* win_name, int width, int height , bool full_sreen, pCycGameTime update, pCycGameTime render);
		virtual ~ShhWindow();		
		virtual bool Initialize();
		virtual bool Initialize(int coord_x, int coord_y);
		virtual bool Start();
		virtual void Release();
		virtual bool Run();
		virtual void Stop();
		virtual IKeyboard* GetKeyborad();
		virtual void SetMinUpdateInterval(int time);
		virtual void SetMinDrawInterval(int time);
		virtual ShhTimeManager* GetTimeManager();
		typedef std::wstring string;
	protected:
		bool BuildWindow(int coord_x, int coord_y);
		bool BuildRenderDevice();
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		
		typedef std::vector<EShhKeys> KeyBuffer;
	// ======================= value ==============================
	protected:
		int			mMaxUpateFreq;
		int			mMaxDrawFreq;
		bool		mRun;
		bool		mFullScreen;
		int			mWinWidth;
		int			mWinHeight;		
		HWND		mWin;
		string		mWinName;
		MSG			mMsg;
		HINSTANCE	mInstance;

		int			mMinUpdateInterval;
		int			mMinDrawInterval;

		pCycGameTime	mUpdateFuc;
		pCycGameTime	mRenderFuc;
		RenderDriver*	mRdDevice;
		HMODULE			mDrvDll;

	public:		
		static ShhWindow* GetWindow();
	};
}

#endif