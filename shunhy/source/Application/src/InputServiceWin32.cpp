#include <WindowsX.h>
#include "InputServiceWin32.h"
#include "Keyboard.h"
#include "Mouse.h"
namespace Shh
{
	LRESULT  InputServerWin32::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (InputServerWin32::CheckSelect())
		{
			return ms_Singleton->_input(hWnd, msg, wParam, lParam);
		}
		
		switch( msg )
		{	
		case WM_DESTROY:
			PostQuitMessage( 0 );
			break;
		case WM_CLOSE:
			break;		
		case WM_QUIT:
			{
			}
		default:
			break;
		}
		return DefWindowProc( hWnd, msg, wParam, lParam );
	}


	SingletonInstancePtr(InputServerWin32);

	InputServerWin32::InputServerWin32()
	{

	}

	InputServerWin32::~InputServerWin32()
	{

	}

	void InputServerWin32::Start()
	{
		ZeroMemory( &mMsg, sizeof(mMsg) );
	}

	bool InputServerWin32::Tick()
	{
		if( PeekMessage( &mMsg, nullptr, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &mMsg );
			DispatchMessage( &mMsg );
			return false;
		}
		return true;
	}

	LRESULT InputServerWin32::_input(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		//static int cout = 0;
		switch( msg )
		{	
		case WM_KEYDOWN:
			//mKeyboard.SetKeyPress((EKeys)wParam);
			_setKey((EKeys)wParam, EKS_Pressed);
			break;
		case WM_KEYUP:
			//mKeyboard.SetKeyUp((EKeys)wParam);
			_setKey((EKeys)wParam, EKS_Released);
			break;
		case WM_SYSKEYDOWN:
			//mKeyboard.SetKeyPress((EKeys)wParam);
			_setKey((EKeys)wParam, EKS_Pressed);
			break;
		case WM_SYSKEYUP:
			//mKeyboard.SetKeyUp((EKeys)wParam);
			_setKey((EKeys)wParam, EKS_Released);
			break;

		case WM_LBUTTONDOWN:
			{
				//mMouse.SetLButtonState(EBS_Pressed);
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				//g_Mouse.SetMousePos(xPos, yPos);
				_setMouse(EBS_MouseL, EKS_Pressed, xPos, yPos);
			}
			break;
		case WM_RBUTTONDOWN:
			{
				//mMouse.SetRButtonState(EBS_Pressed);
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				//g_Mouse.SetMousePos(xPos, yPos);
				_setMouse(EBS_MouseR, EKS_Pressed, xPos, yPos);
			}
			break;
		case WM_MBUTTONDOWN:
			{
				//mMouse.SetMButtonState(EBS_Pressed);
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				//g_Mouse.SetMousePos(xPos, yPos);
				_setMouse(EBS_MouseM, EKS_Pressed, xPos, yPos);
			}
			break;
		case WM_LBUTTONUP:
			{
				//mMouse.SetLButtonState(EBS_Released);
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				//g_Mouse.SetMousePos(xPos, yPos);
				_setMouse(EBS_MouseL, EKS_Released, xPos, yPos);
			}
			break;
		case WM_RBUTTONUP:
			{
				//mMouse.SetRButtonState(EBS_Released);
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				//g_Mouse.SetMousePos(xPos, yPos);
				_setMouse(EBS_MouseR, EKS_Released, xPos, yPos);
			}
			break;
		case WM_MBUTTONUP:
			{
				//mMouse.SetMButtonState(EBS_Released);
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				//g_Mouse.SetMousePos(xPos, yPos);
				_setMouse(EBS_MouseM, EKS_Released, xPos, yPos);
			}
			break;
		case WM_MOUSEWHEEL:
			{

				int fwKeys = GET_KEYSTATE_WPARAM(wParam);
				int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);//返回一个滚动的大小,一般是120的倍数,正数代表滚动向前,负数代表向后
				_addWheel(zDelta);
				//mMouse.AddWheel(zDelta);
				//char buff[128];
				//sprintf(buff, "%s:%d,%d\n", "wheel", zDelta, fwKeys);
				//OutputDebugStringA(buff);
			}
			break;
		case WM_MOUSEMOVE:
			{
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				_setMouseMove(xPos, yPos);
				//mMouse.SetMousePos(xPos, yPos);
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
		case WM_QUIT:
			{
			}
		default:
			break;

		}
		return DefWindowProc( hWnd, msg, wParam, lParam );
	}
}