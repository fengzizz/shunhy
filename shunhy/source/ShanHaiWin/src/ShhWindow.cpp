// ShanHaiWin.cpp : 定义 DLL 应用程序的导出函数。
#include <WindowsX.h>
#include "ShhWindow.h"
#include "ShhTimeManager.h"
#include "ShhKeyboard.h"
#include "ShhMouse.h"
#include "RenderDriver.h"
//#pragma comment(lib,"DrawDrv.lib")
//#pragma comment(lib,"DrawDrv11.lib")

const LPCWSTR gClassName = __TEXT("CShhWinDevice");
const int gDrvDllCount = 2;
#ifdef _DEBUG
const LPCWSTR gDllName[gDrvDllCount] = {L"DrawDrv11_d.dll", L"DrawDrv_d.dll"};
#else
const LPCWSTR gDllName[gDrvDllCount] = {L"DrawDrv11.dll", L"DrawDrv.dll"};
#endif

namespace Shh
{
	ShhWindow*		g_window = nullptr;
	ShhKeyboard		g_keyboard;
	ShhMouse			g_mouse;
	ShhTimeManager		g_game_time;
	IWindow*  g_CreateWindow(const WIN_DESC& desc)
	{
		if (nullptr == g_window)
		{
			g_window = new ShhWindow((HINSTANCE)desc.hInstance, desc.win_name, desc.width, desc.height, desc.full_screen, desc.update, desc.render);
		}
		return (IWindow*)g_window;
	}
	void g_RecycleWindow(IWindow* instance)
	{
		delete instance;
	}

	IKeyboard* g_GetKeyboard()
	{
		return &g_keyboard;
	}

	LRESULT  ShhWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)//
	{
		static int cout = 0;
		switch( msg )
		{	
		case WM_KEYDOWN:
			g_keyboard.SetKeyPress((EShhKeys)wParam);
			break;
		case WM_KEYUP:
			g_keyboard.SetKeyUp((EShhKeys)wParam);
			break;
		case WM_SYSKEYDOWN:
			g_keyboard.SetKeyPress((EShhKeys)wParam);
			break;
		case WM_SYSKEYUP:
			g_keyboard.SetKeyUp((EShhKeys)wParam);
			break;

		case WM_LBUTTONDOWN:
			{
				g_mouse.SetLButtonState(EShhBS_Pressed);
				//int xPos = GET_X_LPARAM(lParam); 
				//int yPos = GET_Y_LPARAM(lParam); 
				//g_Mouse.SetMousePos(xPos, yPos);
			}
			break;
		case WM_RBUTTONDOWN:
			{
				g_mouse.SetRButtonState(EShhBS_Pressed);
				//int xPos = GET_X_LPARAM(lParam); 
				//int yPos = GET_Y_LPARAM(lParam); 
				//g_Mouse.SetMousePos(xPos, yPos);
			}
			break;
		case WM_MBUTTONDOWN:
			{
				g_mouse.SetMButtonState(EShhBS_Pressed);
				//int xPos = GET_X_LPARAM(lParam); 
				//int yPos = GET_Y_LPARAM(lParam); 
				//g_Mouse.SetMousePos(xPos, yPos);
			}
			break;
		case WM_LBUTTONUP:
			{
				g_mouse.SetLButtonState(EShhBS_Released);
				//int xPos = GET_X_LPARAM(lParam); 
				//int yPos = GET_Y_LPARAM(lParam); 
				//g_Mouse.SetMousePos(xPos, yPos);
			}
			break;
		case WM_RBUTTONUP:
			{
				g_mouse.SetRButtonState(EShhBS_Released);
				//int xPos = GET_X_LPARAM(lParam); 
				//int yPos = GET_Y_LPARAM(lParam); 
				//g_Mouse.SetMousePos(xPos, yPos);
			}
			break;
		case WM_MBUTTONUP:
			{
				g_mouse.SetMButtonState(EShhBS_Released);
				//int xPos = GET_X_LPARAM(lParam); 
				//int yPos = GET_Y_LPARAM(lParam); 
				//g_Mouse.SetMousePos(xPos, yPos);
			}
			break;
		case WM_MOUSEWHEEL:
			{
				
				int fwKeys = GET_KEYSTATE_WPARAM(wParam);
				int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);//返回一个滚动的大小,一般是120的倍数,正数代表滚动向前,负数代表向后

				g_mouse.AddWheel(zDelta);
				//char buff[128];
				//sprintf(buff, "%s:%d,%d\n", "wheel", zDelta, fwKeys);
				//OutputDebugStringA(buff);
			}
			break;
		case WM_MOUSEMOVE:
			{
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				g_mouse.SetMousePos(xPos, yPos);
				//char buff[128];
				//sprintf(buff, "%s:%d,%d\n", "move", xPos, yPos);
				//OutputDebugStringA(buff);
			}
			break;

		case WM_DESTROY:
			PostQuitMessage( 0 );
			break;
		case WM_CLOSE:
			break;				
		default:
			break;

		}
		return DefWindowProc( hWnd, msg, wParam, lParam );
	};


	ShhWindow::ShhWindow(HINSTANCE hInstance, wchar_t* win_name, int width, int height , bool full_sreen, pCycGameTime update, pCycGameTime render)
		: mWinName(win_name), mWinWidth(width), mWinHeight(height), mFullScreen(full_sreen), mUpdateFuc(update), mRenderFuc(render)
		, mRun(false), mMinUpdateInterval(40), mMinDrawInterval(0)
		, mRdDevice(nullptr), mDrvDll(nullptr)
	{
		if (nullptr == hInstance)
		{
			mInstance = GetModuleHandle(nullptr);
		}
		else
		{
			mInstance = hInstance;
		}
		//ShhGameTime* Gametime = ShhGameTime::GetSingletonPtr();
	}
	ShhWindow::~ShhWindow()
	{
		Release();
	}
	bool ShhWindow::Initialize()
	{
		return Initialize(100, 100);
	}

	bool ShhWindow::Initialize(int coord_x, int coord_y)
	{
		if (BuildWindow(coord_x, coord_y))
		{
			return BuildRenderDevice();			
		}
		return false;
	}
	ShhWindow* ShhWindow::GetWindow()
	{
		return g_window;
	}
	bool ShhWindow::Start()
	{
		ZeroMemory( &mMsg, sizeof(mMsg) );
		if(ShowWindow(mWin, SW_SHOW))
		{
			if(UpdateWindow(mWin))
			{
				SetFocus(mWin);
				mRun = true;
				return true;
			}
		}
		return false;
	}
	void ShhWindow::Stop()
	{
		mRun = false;
	}
	bool ShhWindow::Run()
	{		
		//进入消息循环
		if (mRun && mMsg.message !=  WM_QUIT)//WM_DESTROY
		{
			if( PeekMessage( &mMsg, nullptr, 0U, 0U, PM_REMOVE ) )
			{
				TranslateMessage( &mMsg );
				DispatchMessage( &mMsg );
			}
			else
			{
				//g_keyboard.Present();
				//g_mouse.Present();
				//mUpdateFuc(nullptr);
				//mRdDevice->DrawBegin();
				//mRenderFuc(nullptr);
				//mRdDevice->DrawEnd();

			}
			return true;
		}
		return false;
	}
	void ShhWindow::Release()
	{
		UnregisterClass( gClassName, mInstance );//GetModuleHandle(nullptr)
		DestroyWindow(mWin);
		recycleDrvFunc func = nullptr;
		func = (recycleDrvFunc)GetProcAddress (mDrvDll, "g_RecycleRenderDevice");
		func(mRdDevice);
		mRdDevice = nullptr;

		if (mDrvDll)
		{
			FreeLibrary(mDrvDll);
			mDrvDll = nullptr;
		}
	}

	bool ShhWindow::BuildWindow(int coord_x, int coord_y)
	{
		//注册窗口类

		//HINSTANCE hInstance = GetModuleHandle(nullptr);
		// Register Class
		WNDCLASSEX wcex;
		//WNDCLASS wcex;
		wcex.cbSize			= sizeof(WNDCLASSEX);
		wcex.style			=  CS_DBLCLKS;//CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= WndProc;//ShhWindow::
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
			mWinWidth = GetSystemMetrics(SM_CXSCREEN);
			mWinHeight = GetSystemMetrics(SM_CYSCREEN);
			coord_x = coord_y = 0;
			dwStyle = WS_POPUP;
		}


		mWin = CreateWindowEx(WS_EX_APPWINDOW, gClassName, mWinName.c_str(),
			dwStyle, coord_x, coord_y, mWinWidth, mWinHeight,
			nullptr, nullptr, wcex.hInstance, nullptr );

		return nullptr != mWin;
	}
	bool ShhWindow::BuildRenderDevice()
	{
		for (int i = 0; i < gDrvDllCount; ++i)
		{		
			mDrvDll = LoadLibrary(gDllName[i]);
			if (mDrvDll)
			{
				createDrvFunc func = nullptr;
				func = (createDrvFunc)GetProcAddress (mDrvDll, "g_CreateRenderDevice");
				if (func)
				{
					DRV_DESC desc;
					desc.width = mWinWidth;
					desc.height = mWinHeight;
					desc.full_screen = mFullScreen;
					desc.stencil_buffer = true;
					desc.handle = (size_t)mWin;
					mRdDevice = func(desc);
					//_iRdDevice = Shh::g_CreateRenderDevice(_iWinWidth,_iWinHeight,_bFullScreen,1, _hWin);
					if (mRdDevice->Initialize())
					{
						return true;
					}
					else
					{
						mRdDevice->Release();
						delete mRdDevice;
						mRdDevice = nullptr;
					}
				}
			}
		}
		return false;
	}

	IKeyboard* ShhWindow::GetKeyborad()
	{
		return &g_keyboard;
	}
	ShhTimeManager* ShhWindow::GetTimeManager()
	{
		return &g_game_time;
	}
	void ShhWindow::SetMinDrawInterval(int time)
	{
		mMinDrawInterval = time;
	}
	void ShhWindow::SetMinUpdateInterval(int time)
	{
		mMinUpdateInterval = time;
	}
}