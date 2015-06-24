#pragma once
//#include "IRelease.h"
#include "WinConfig.h"
#include "TimeManager.h"
#include "Keyboard.h"
#include "IRelease.h"
#include "TimeManager.h"
//#pragma comment(lib,"DrawDrv.lib")

//using namespace Shh;


namespace Shh
{
	typedef void (*pCycGameTime) (const GameTime*);

	class WIN_DESC
	{
	public:		
		WIN_DESC();
		size_t hInstance;
		size_t width;
		size_t height;
		wchar_t* win_name;		
		pCycGameTime update;
		pCycGameTime render;
		bool full_screen;

	};
	inline WIN_DESC::WIN_DESC()
		:hInstance(0)
		,width(0)
		,height(0)
		,win_name(nullptr)
		,full_screen(false)
		,update(nullptr)
		,render(nullptr)
	{
	}

	class SHH_WIN_API IWindow : public IRelease//SHH_WIN_API
	{
	public:
		//IshWindow();
		virtual ~IWindow() {};
		virtual void SetMinUpdateInterval(int time) = 0;
		virtual void SetMinDrawInterval(int time) = 0;
		virtual bool Start() = 0;
		virtual bool Run() = 0;
		virtual void Stop() = 0;
		virtual bool Initialize() = 0;
		virtual bool Initialize(int coord_x, int coord_y) = 0;
		virtual void Release() = 0;
		virtual IKeyboard* GetKeyborad() = 0;
		//virtual ITimeManager* GetTimeManager() = 0;
	};
	extern "C"{//////ShhCALLCONV
	SHH_WIN_API IWindow*  g_CreateWindow(const WIN_DESC& desc);
	SHH_WIN_API void g_RecycleWindow(IWindow* instance);
	}
	typedef Shh::IWindow* (* createWinFunc)(const WIN_DESC& desc);
	typedef void (* recycleWinFunc)(IWindow* instance);
}