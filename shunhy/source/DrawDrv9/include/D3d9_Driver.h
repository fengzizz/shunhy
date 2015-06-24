#pragma once
#include "RenderDriver.h"
#include "D3d9_Common.h"

using namespace Shh;

namespace Shh
{
	class D3d9Driver : RenderDriver
	{
	public:
		D3d9Driver(int width, int height, bool full_screen, bool stencil_buffer, HWND window);
		~D3d9Driver();
		virtual bool Initialize() override;
		virtual void Release() override;		
		virtual void DrawBegin() override;
		virtual void DrawEnd() override;
		virtual DrawDrvCode GetDrawDrvType() override;
		virtual ResourceFactory* GetResourceFactory() const override;

		virtual void UpdateConstBuffer_Camera(const CBufferCamera& buffer) override;
		virtual void UpdateConstBuffer_Object(const CBufferObject& buffer) override;

		IDirect3D9* GetD3d9() const;
		IDirect3DDevice9* GetD3d9Device() const;
	private:
		D3DPRESENT_PARAMETERS		mD3dpp;
		IDirect3D9*					mD3d;				//Direct3D对象
		IDirect3DDevice9*			mD3dDevice;		//Direct3D设备对象
		HWND						mWindowHwnd;		//窗口句柄

		D3d9ResourceFactory*		mResourceFactory;

		int		mBackBufferWidth;
		int		mBackBufferHeight;
		bool	mIsFullScreen;
		bool	mIsStencilBuffer;

		static const DrawDrvCode sDrawDrvType;
	};
	inline IDirect3D9* D3d9Driver::GetD3d9() const
	{
		return mD3d;
	}
	inline IDirect3DDevice9*  D3d9Driver::GetD3d9Device() const
	{
		return mD3dDevice;
	}
}