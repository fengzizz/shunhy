#pragma once
#include <Windows.h>
#include "Core/Singleton.h"
#include "Core/U16String.h"
#include "Application/AppDef.h"
#include "PrivateDef.h"


namespace Shh
{
	class DisplayWin32 : public Singleton<DisplayWin32>
	{
		__Dynamic_Alloc(DisplayWin32)
	public:
		bool Show();
		void Destroy();
		size_t GetHandle() const;
		void Setup(const APP_DESC& desc);
	private:
		DisplayWin32();
		~DisplayWin32();
		size_t mWidth;
		size_t mHeight;
		U16String mName;
		HINSTANCE mInstance;
		HWND	mWinHandle;
		bool mFullScreen;
	};

	inline size_t DisplayWin32::GetHandle() const
	{
		return (size_t)mWinHandle;
	}
}