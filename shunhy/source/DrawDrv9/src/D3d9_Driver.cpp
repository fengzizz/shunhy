#include "D3d9_Driver.h"
#if __Renderer_d3d9__

const DrawDrvCode D3d9Driver::sDrawDrvType = DrawDrv_D3D9;

namespace Shh
{
	RenderDriver* g_CreateRenderDevice(const DRV_DESC& desc)
	{
		D3d9Driver* pdrv = shh_new D3d9Driver(desc.width, desc.height, desc.full_screen, desc.stencil_buffer, (HWND)desc.handle);			

		return (RenderDriver*)pdrv;

		//return nullptr;
	}
	void g_RecycleRenderDevice(RenderDriver* instance)
	{
		shh_delete instance;
	}

	D3d9Driver::D3d9Driver(int width, int height, bool full_screen, bool stencil_buffer, HWND window)
		:mD3d(nullptr), mD3dDevice(nullptr), mBackBufferWidth(width), mBackBufferHeight(height),
		mIsFullScreen(full_screen), mIsStencilBuffer(stencil_buffer), mWindowHwnd(window)
	{
	}
	D3d9Driver::~D3d9Driver()
	{
		Release();
	}
	DrawDrvCode D3d9Driver::GetDrawDrvType()
	{
		return D3d9Driver::sDrawDrvType;
	}

	ResourceFactory* D3d9Driver::GetResourceFactory() const
	{
		return (ResourceFactory*)mResourceFactory;
	}

	void D3d9Driver::UpdateConstBuffer_Camera(const CBufferCamera& buffer)
	{

	}

	void D3d9Driver::UpdateConstBuffer_Object(const CBufferObject& buffer)
	{

	}


	bool D3d9Driver::Initialize()
	{
		//======================== 创建Direct3D对象, 该对象用于创建Direct3D设备对象 ============================================================
		if( nullptr == ( mD3d = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		{
			Release();
			return false;
		}

		//======================== 设置D3DPRESENT_PARAMETERS结构, 准备创建Direct3D设备对象 ================================================
		D3DDISPLAYMODE d3ddm;
		mD3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

		ZeroMemory(&mD3dpp, sizeof(mD3dpp));

		mD3dpp.BackBufferCount		= 1;
		mD3dpp.EnableAutoDepthStencil	= TRUE;
		mD3dpp.PresentationInterval = D3DPRESENT_RATE_DEFAULT;
		mD3dpp.hDeviceWindow = mWindowHwnd;
		mD3dpp.BackBufferWidth	= mBackBufferWidth;
		mD3dpp.BackBufferHeight = mBackBufferHeight;
		if (mIsFullScreen)
		{
			mD3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
			mD3dpp.SwapEffect		= D3DSWAPEFFECT_FLIP;
			mD3dpp.Windowed			= FALSE;
			mD3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		}
		else
		{
			mD3dpp.BackBufferFormat	= d3ddm.Format;
			mD3dpp.SwapEffect		= D3DSWAPEFFECT_DISCARD;
			mD3dpp.Windowed			= TRUE;
		}
		UINT adapter = D3DADAPTER_DEFAULT;
		D3DDEVTYPE devtype = D3DDEVTYPE_HAL;
		
		//==================================== 抗锯齿设置（暂略）========================================================================

		//==================================== 模板缓冲设置 ========================================================================
		if (mIsStencilBuffer)
		{
			mD3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
			if(FAILED(mD3d->CheckDeviceFormat(adapter, devtype,
				mD3dpp.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL,
				D3DRTYPE_SURFACE, mD3dpp.AutoDepthStencilFormat)))
			{
				mD3dpp.AutoDepthStencilFormat = D3DFMT_D24X4S4;
				if(FAILED(mD3d->CheckDeviceFormat(adapter, devtype,
					mD3dpp.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL,
					D3DRTYPE_SURFACE, mD3dpp.AutoDepthStencilFormat)))
				{
					mD3dpp.AutoDepthStencilFormat = D3DFMT_D15S1;
					if(FAILED(mD3d->CheckDeviceFormat(adapter, devtype,
						mD3dpp.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL,
						D3DRTYPE_SURFACE, mD3dpp.AutoDepthStencilFormat)))
					{
						mIsStencilBuffer = false;
					}
				}
			}
			else if(FAILED(mD3d->CheckDepthStencilMatch(adapter, devtype,
					mD3dpp.BackBufferFormat, mD3dpp.BackBufferFormat, mD3dpp.AutoDepthStencilFormat)))
				{
					mIsStencilBuffer = false;
				}
		}		
		else// do not use else here to cope with flag change in previous block
		{
			mD3dpp.AutoDepthStencilFormat = D3DFMT_D32;
			if(FAILED(mD3d->CheckDeviceFormat(adapter, devtype,
				mD3dpp.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL,
				D3DRTYPE_SURFACE, mD3dpp.AutoDepthStencilFormat)))
			{
				mD3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;
				if(FAILED(mD3d->CheckDeviceFormat(adapter, devtype,
					mD3dpp.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL,
					D3DRTYPE_SURFACE, mD3dpp.AutoDepthStencilFormat)))
				{
					mD3dpp.AutoDepthStencilFormat = D3DFMT_D16;
					if(FAILED(mD3d->CheckDeviceFormat(adapter, devtype,
						mD3dpp.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL,
						D3DRTYPE_SURFACE, mD3dpp.AutoDepthStencilFormat)))
					{
						return false;
					}
				}
			}
		}


		//==================================== 创建Direct3D设备对象  ========================================================================
		if( FAILED( mD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, nullptr,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&mD3dpp, &mD3dDevice ) ) )
		{
			//return E_FAIL;
			Release();
			return false;
		}

		//设置剔出模式为不剔出任何面(正面和方面)
		mD3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

		//启用深度测试
		mD3dDevice->SetRenderState( D3DRS_ZENABLE, true );

		//开启Alpha混合
		mD3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, false );
		mD3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		mD3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		return true;

	}
	void D3d9Driver::Release()
	{
		D3d9Common::DeleteCOMptr(mD3dDevice);
		D3d9Common::DeleteCOMptr(mD3d);
	}
	void D3d9Driver::DrawBegin()
	{
		mD3dDevice->BeginScene();
		
		mD3dDevice->Clear(0, nullptr, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 0x0000ff, 1.0f, 0);
	}
	void D3d9Driver::DrawEnd()
	{
		mD3dDevice->EndScene();
		mD3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
	}
}

#endif