#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Core/Singleton.h"
#include "Core/UniquePtr.h"
#include "Core/U16String.h"
#include "Application/AppDef.h"


#define APPLICATION_FORCE_NvOptimusEnablement \
extern "C"\
{\
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;\
}


namespace Shh
{

	class _Shh_Export APP_DESC
	{
	public:		
		APP_DESC();
		int coord_x;
		int coord_y;
		size_t hInstance;
		size_t width;
		size_t height;
		U16String* name;
		U16String* working_path;
		ApplicationListener* listener;
		bool full_screen;
	};
	inline APP_DESC::APP_DESC()
		:hInstance(0)
		,width(0)
		,height(0)
		,name(nullptr)
		,working_path(nullptr)
		,full_screen(false)
		,listener(nullptr)
	{
	}

	class _Shh_Export ApplicationListener
	{
	public:
		virtual ~ApplicationListener();
		virtual void OnStart() = 0;
		virtual void OnScript() = 0;
		virtual void OnStop() = 0;
		virtual void OnExit() = 0;
	protected:
		ApplicationListener();
	};

	class _Shh_Export Application : public Singleton<Application>
	{
	public:
		Application();
		virtual ~Application();
		virtual void Setup(const APP_DESC& desc);
		virtual bool Start();
		virtual void Destroy();
		virtual void Run();
		virtual void Stop();

		Keyboard& GetKeyboard() const;
		Mouse& GetMouse() const;
	private:
		AppCore* mCore;
	};
}
#endif	//__APPLICATION_H__