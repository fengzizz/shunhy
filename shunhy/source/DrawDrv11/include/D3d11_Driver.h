#pragma once
#include "Core/Singleton.h"
#include "RenderDriver.h"
#include "D3d11_Common.h"
#include "Core/U8String.h"
#include "D3d11_SystemBuffer.h"
//using namespace Shh;

namespace Shh
{
	class D3d11Driver : public RenderDriver , public Singleton<D3d11Driver>
	{
	public:
		D3d11Driver(int width, int height, bool full_screen, bool stencil_buffer, HWND window);
		~D3d11Driver();
		virtual bool Initialize() override;
		virtual void SetShaderProgram(GPUProgram* program) override;
		virtual void Release() override;
		virtual void DrawBegin() override;
		virtual void Draw(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, InputLayout* layout) override;
		virtual void DrawEnd() override;
		virtual DrawDrvCode GetDrawDrvType() override;

		virtual ResourceFactory* GetResourceFactory() const override;
		virtual void UpdateConstBuffer_Camera(const CBufferCamera& buffer) override;
		virtual void UpdateConstBuffer_Object(const CBufferObject& buffer) override;

		const D3d11SystemBuffer& GetD3d11SystemBuffer() const;
		D3d11SystemBuffer& GetD3d11SystemBuffer();

		ID3D11Device* GetD3d11Device() const;
		ID3D11DeviceContext* GetD3D11DeviceContext() const;

	private:
		bool checkAdapter(IDXGIAdapter1* adapter);

		D3d11SystemBuffer	mSysConstBuffer;

		IDXGIFactory1*						mDXGIFactory;
		ID3D11Device*                       mD3dDevice;
		ID3D11DeviceContext*                mImmediateContext;
		IDXGISwapChain*                     mSwapChain;
		D3d11ResourceFactory*				mResourceFactory;

		//ID3D11Texture2D*                    mRenderTarget;
		ID3D11RenderTargetView*             mRenderTargetView;
		//ID3D11Texture2D*                    mDepthStencil;
		ID3D11DepthStencilView*             mDepthStencilView;
		ID3D11VertexShader*                 mVertexShader;
		ID3D11PixelShader*                  mPixelShader;
		ID3D11InputLayout*                  mVertexLayout;
		U8String							mVideoCardName;
		int									mVideoCardMemory;
		D3D_DRIVER_TYPE                     mDriverType;
		D3D_FEATURE_LEVEL                   mFeatureLevel;
		HWND	mWindowHwnd;		//窗口句柄
		int		mBackBufferWidth;
		int		mBackBufferHeight;
		bool	mIsFullScreen;
		bool	mIsStencilBuffer;


		static const DrawDrvCode sDrawDrvType;
	};

	inline D3d11SystemBuffer& D3d11Driver::GetD3d11SystemBuffer()
	{
		return mSysConstBuffer;
	}

	inline const D3d11SystemBuffer& D3d11Driver::GetD3d11SystemBuffer() const
	{
		return mSysConstBuffer;
	}

	inline ID3D11Device*  D3d11Driver::GetD3d11Device() const
	{
		return mD3dDevice;
	}

	inline ID3D11DeviceContext* D3d11Driver::GetD3D11DeviceContext() const
	{
		return mImmediateContext;
	}
}