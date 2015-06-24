#include "Core/CoreService.h"
#include "Core/Convert.h"
#include "Display.h"
#include "GameService.h"
#include "InputService.h"
#include "AppInputListener.h"
#include "Application.h"
#include "AppCore.h"
namespace Shh
{
	AppCore::AppCore()
		:mRun(false)
		,mListener(nullptr)
	{

	}
	AppCore::~AppCore()
	{
	}
	void AppCore::Setup(const APP_DESC& desc)
	{
		shh_assert(mDisplay.empty());
		shh_assert(mGameService.empty());
		shh_assert(mInputService.empty());
		shh_assert(mCoreService.empty());
		mDisplay.create();
		mCoreService.create();
		mGameService.create();
		mInputService.create();
		mInputListener.create();


		mListener = desc.listener;

		String path;
		utility::toUtf8(*(desc.working_path), path);

		mCoreService->Setup(path);
		mDisplay->Setup(desc);
		mGameService->Setup(desc.width, desc.height, mDisplay->GetHandle(), desc.full_screen);
	}

	bool AppCore::Start()
	{

		mInputService->Start();
		shh_assert(!mRun);
		if (Display::GetSingleton().Show())
		{
			GameService::GetSingleton().Start();
			if (mListener)
			{
				mListener->OnStart();
			}
			return true;
		}
		return false;
	}
	void AppCore::Stop()
	{
		shh_assert(mRun);
		mRun = false;
		if (mListener)
		{
			mListener->OnStop();
		}
	}
	void AppCore::Destroy()
	{
		if (mListener)
		{
			mListener->OnExit();
		}

		mDisplay->Destroy();
		mGameService->Destroy();
		mCoreService->Destroy();
	}
	void AppCore::Run()
	{
		mRun = true;
		mInputService->AddListener(mInputListener.get());
		InputService::GetSingleton().SetSelect(true);
		//进入消息循环
		while(mRun)//WM_DESTROY
		{
			if (mInputService->Tick())
			{
				if (mListener)
				{
					mListener->OnScript();
				}
				mGameService->Tick();
			}
			if(mInputService->CheckExitEvent())
			{
				break;
			}
		}
		mInputService->SetSelect(false);
	}

}