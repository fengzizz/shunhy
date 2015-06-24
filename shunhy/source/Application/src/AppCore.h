#ifndef __APPCORE_H__
#define __APPCORE_H__
#include "Core/Log.h"
#include "Core/UniquePtr.h"
#include "AppDef.h"
#include "PrivateDef.h"

namespace Shh
{
	class AppCore
	{
	public:
		AppCore();
		~AppCore();
		void Setup(const APP_DESC& desc);
		bool Start();
		void Destroy();
		void Run();
		void Stop();

		AppInputListener* GetListener() const;

	private:
		uptr<Display> mDisplay;
		uptr<CoreService> mCoreService;
		uptr<GameService> mGameService;
		uptr<InputService> mInputService;
		uptr<AppInputListener> mInputListener;
		ApplicationListener* mListener;
		bool mRun;
	};

	inline AppInputListener* AppCore::GetListener() const
	{
		return mInputListener.get();
	}
}

#endif //__APPCORE_H__