#include "PrivateDef.h"
#include "DisplayWin32.h"
#include "Application.h"
#include "InputService.h"

namespace Shh
{
	LPCWSTR gClassName = __TEXT("CShhApplication");
	SingletonInstancePtr(DisplayWin32);

	DisplayWin32::DisplayWin32()
	{

	}
	DisplayWin32::~DisplayWin32()
	{

	}


	bool DisplayWin32::Show()
	{
		if(ShowWindow(mWinHandle, SW_SHOW))
		{
			if(UpdateWindow(mWinHandle))
			{
				SetFocus(mWinHandle);
				return true;
			}
		}
		return false;
	}
	void DisplayWin32::Destroy()
	{
		UnregisterClass( gClassName, mInstance );//GetModuleHandle(nullptr)
		DestroyWindow(mWinHandle);
	}

	void DisplayWin32::Setup(const APP_DESC& desc)
	{
		if (desc.hInstance)
		{
			mInstance = (HINSTANCE)desc.hInstance;
		}
		else
		{
			mInstance = GetModuleHandle(NULL);
		} 
		mWidth = desc.width;
		mHeight = desc.height;
		mName = *(desc.name);
		mFullScreen = desc.full_screen;
		int coord_x = desc.coord_x;
		int coord_y = desc.coord_y;

		//注册窗口类

		WNDCLASSEX wcex;
		wcex.cbSize			= sizeof(WNDCLASSEX);
		wcex.style			= CS_DBLCLKS;//CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= InputService::WndProc;//ShhWindow::
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= mInstance;
		wcex.hIcon			= nullptr;
		wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= 0;
		wcex.lpszClassName	= gClassName;
		wcex.hIconSm		= 0;

		// if there is an icon, load it

		RegisterClassEx(&wcex);
		//RegisterClass(&wcex);
		//创建窗口
		///////////////WS_OVERLAPPEDWINDOW;//
		DWORD dwStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		if (mFullScreen)
		{
			mWidth = GetSystemMetrics(SM_CXSCREEN);
			mHeight = GetSystemMetrics(SM_CYSCREEN);
			coord_x = coord_y = 0;
			dwStyle = WS_POPUP;
		}


		mWinHandle = CreateWindowEx(WS_EX_APPWINDOW, gClassName, (LPCWSTR)mName.c_str(),
			dwStyle, coord_x, coord_y, mWidth, mHeight,
			NULL, NULL, wcex.hInstance, NULL );
	}
}