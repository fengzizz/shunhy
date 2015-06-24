
#include "AppCore.h"
#include "AppInputListener.h"
#include "Application.h"
namespace Shh
{

	ApplicationListener::ApplicationListener()
	{

	}

	ApplicationListener::~ApplicationListener()
	{

	}

	SingletonInstancePtr(Application);
	Application::Application()
		:mCore(nullptr)
	{
	}
	Application::~Application()
	{
	}
	void Application::Setup(const APP_DESC& desc)
	{
		shh_assert(nullptr == mCore);
		mCore = shh_new AppCore();
		mCore->Setup(desc);
	}

	bool Application::Start()
	{
		shh_assert(mCore);
		shh_log("application start.");
		return mCore->Start();
	}
	void Application::Stop()
	{
		shh_assert(mCore);
		shh_log("application stop.");
		mCore->Stop();
	}

	void Application::Run()
	{	
		shh_assert(mCore);
		shh_log("application run begin.");
		mCore->Run();
		shh_log("application run end.");
	}

	void Application::Destroy()
	{
		shh_assert(mCore);
		shh_log("application destroy.");
		mCore->Destroy();
		shh_delete mCore;
	}
	
	Keyboard& Application::GetKeyboard() const
	{
		return mCore->GetListener()->GetKeyboard();
	}
	Mouse& Application::GetMouse() const
	{
		return mCore->GetListener()->GetMouse();
	}
}