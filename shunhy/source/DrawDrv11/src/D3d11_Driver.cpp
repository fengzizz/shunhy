#include "Core/Convert.h"
#include "D3d11_Utility.h"
#include "D3d11_InputLayout.h"
#include "D3d11_VertexShader.h"
#include "D3d11_VertexBuffer.h"
#include "D3d11_PixelShader.h"
#include "D3d11_GPUProgram.h"
#include "D3d11_VertexBuffer.h"
#include "D3d11_IndexBuffer.h"
#include "D3d11_ResourceFactory.h"
#include "D3d11_Driver.h"



#if __Renderer_d3d11__

#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#define HR(x)
namespace Shh
{
	const DrawDrvCode D3d11Driver::sDrawDrvType = DrawDrv_D3D11;
	RenderDriver* g_CreateRenderDevice(const DRV_DESC& desc)
	{
		D3d11Driver* pdrv = shh_new D3d11Driver(desc.width, desc.height, desc.full_screen, desc.stencil_buffer, (HWND)desc.handle);
		return (RenderDriver*)pdrv;
	}

	void g_RecycleRenderDevice(RenderDriver* instance)
	{
		shh_delete instance;
	}

	SingletonInstancePtr(D3d11Driver);
	D3d11Driver::D3d11Driver(int width, int height, bool full_screen, bool stencil_buffer, HWND window)
		:mBackBufferWidth(width)
		,mBackBufferHeight(height)
		,mIsFullScreen(full_screen)
		,mIsStencilBuffer(stencil_buffer)
		,mWindowHwnd(window)

		,mDriverType(D3D_DRIVER_TYPE_NULL)
		,mFeatureLevel(D3D_FEATURE_LEVEL_11_0)
		,mDXGIFactory(nullptr)
		,mD3dDevice(nullptr)
		,mImmediateContext(nullptr)		
		,mSwapChain(nullptr)
		,mResourceFactory(nullptr)
		,mRenderTargetView(nullptr)
		,mDepthStencilView(nullptr)
		,mVertexShader(nullptr)
		,mPixelShader(nullptr)
		,mVertexLayout(nullptr)
	{
	}
	D3d11Driver::~D3d11Driver()
	{
		Release();
	}
	DrawDrvCode D3d11Driver::GetDrawDrvType()
	{
		return D3d11Driver::sDrawDrvType;
	}
	bool D3d11Driver::checkAdapter(IDXGIAdapter1* adapter)
	{
		HRESULT result;     
		IDXGIOutput* adapterOutput;    
		unsigned int numModes = 0;  
		DXGI_MODE_DESC* displayModeList;    
		DXGI_ADAPTER_DESC adapterDesc;     
  
    
		// 得到适配器的输出.    
		result = adapter->EnumOutputs(0, &adapterOutput);    
		if(FAILED(result))    
		{      
			return false;    
		}    
    
		//得到适合 DXGI_FORMAT_R8G8B8A8_UNORM 的显示模式.    //DXGI_FORMAT_R8G8B8A8_UNORM
		result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);    
		if(FAILED(result))    
		{      
			return false;    
		}
    
		displayModeList = shh_new DXGI_MODE_DESC[numModes];    
    
		// 保存显示模式到displayModeList中    //DXGI_FORMAT_R8G8B8A8_UNORM_SRGB
		result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);    
		if(FAILED(result))    
		{   
			return false;    
		}    
    
		////遍历所有显示模式，得到刷新率两个参数值numerator 和 denominato    
		//for(unsigned int i = 0; i < numModes; i++)    
		//{    
		//	if(displayModeList[i].Width == (unsigned int)mBackBufferWidth)    
		//	{    
		//		if(displayModeList[i].Height == (unsigned int)mBackBufferHeight)    
		//		{    
		//			//numerator = displayModeList[i].RefreshRate.Numerator;    
		//			//denominator = displayModeList[i].RefreshRate.Denominator; 
		//			//desc.BufferDesc = displayModeList[i];
		//			break;    
		//		}    
		//	}    
		//}    
		//desc.BufferDesc.RefreshRate.Numerator = 60;//0;//打开垂直同步。//
		//desc.BufferDesc.RefreshRate.Denominator = 1;
		// 得到显卡描述    
		result = adapter->GetDesc(&adapterDesc);    
		if(FAILED(result))    
		{      
			return false;    
		}    
    
		// 保存显存大小.    
		mVideoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);    
    
		//保存显卡描述串
		U16String card_name = (char16_t*)adapterDesc.Description;
		utility::toUtf8(card_name, mVideoCardName);
		// 释放显示模式列表    
		shh_delete [] displayModeList;    
		displayModeList = 0;    
    
		//释放适配器输出.    
		adapterOutput->Release();    
		adapterOutput = 0;    
    
		return true;
	}
	bool D3d11Driver::Initialize()
	{

		UINT createDeviceFlags = 0;
		//#ifdef _DEBUG
		//    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		//#endif

		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_UNKNOWN,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};
		UINT numDriverTypes = ARRAYSIZE( driverTypes );

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1,
		};
		UINT numFeatureLevels = ARRAYSIZE( featureLevels );


		HRESULT hr;

		hr = CreateDXGIFactory1(__uuidof( IDXGIFactory1 ), ( LPVOID* )&mDXGIFactory );
		if( FAILED( hr ) )
			return false;

		IDXGIAdapter1* adapter = NULL;
		hr = mDXGIFactory->EnumAdapters1( 0, &adapter );
		if ( FAILED( hr) ) 
		{
			return false;
		}

		checkAdapter(adapter);

		for(UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
		{
			mDriverType = driverTypes[driverTypeIndex];//mDriverType//numFeatureLevelspAdapter
			hr = D3D11CreateDevice(adapter, mDriverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
				D3D11_SDK_VERSION, &mD3dDevice, &mFeatureLevel, &mImmediateContext);
			if( SUCCEEDED( hr ) )
			{
				break;
			}
		}
		adapter->Release();
		adapter = NULL;
		if( FAILED( hr ) )
			return false;

		DECL_ZERO(DXGI_SWAP_CHAIN_DESC, swapChainDesc);


		swapChainDesc.BufferDesc.Width = mBackBufferWidth;
		swapChainDesc.BufferDesc.Height = mBackBufferHeight;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;	// use 0 to avoid a potential mismatch with hw
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;	//use 0 to avoid a potential mismatch with hw
		swapChainDesc.BufferDesc.Format = (DXGI_FORMAT)DXGI_FORMAT_R10G10B10A2_UNORM;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;


		// MSAA Sample count
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		// 1:single buffering, 2:double buffering, 3:triple buffering
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = mWindowHwnd;
		swapChainDesc.Windowed = !mIsFullScreen;
		// DXGI_SWAP_EFFECT_DISCARD / DXGI_SWAP_EFFECT_SEQUENTIAL
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


		hr = mDXGIFactory->CreateSwapChain(mD3dDevice, &swapChainDesc, &mSwapChain);
		if( FAILED( hr ) )
			return false;

		switch(mFeatureLevel)
		{
		case D3D_FEATURE_LEVEL_11_0:
			{
				shh_log("D3D_FEATURE_LEVEL: D3D_FEATURE_LEVEL_11_0");
			}
			break;	
		case D3D_FEATURE_LEVEL_10_1:
			{
				shh_log("D3D_FEATURE_LEVEL: D3D_FEATURE_LEVEL_10_1");
			}
			break;	
		case D3D_FEATURE_LEVEL_10_0:
			{
				shh_log("D3D_FEATURE_LEVEL: D3D_FEATURE_LEVEL_10_0");
			}
			break;	
		case D3D_FEATURE_LEVEL_9_3:
			{
				shh_log("D3D_FEATURE_LEVEL: D3D_FEATURE_LEVEL_9_3");
			}
			break;	
		case D3D_FEATURE_LEVEL_9_2:
			{
				shh_log("D3D_FEATURE_LEVEL: D3D_FEATURE_LEVEL_9_2");
			}
			break;	
		case D3D_FEATURE_LEVEL_9_1:
			{
				shh_log("D3D_FEATURE_LEVEL: D3D_FEATURE_LEVEL_9_1");
			}
			break;	
		default:
			break;
		}

		mResourceFactory =  shh_new D3d11ResourceFactory(this);

		// Create a render target view
		ID3D11Texture2D* pBackBuffer = NULL;
		hr = mSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
		if( FAILED( hr ) )
			return false;

		hr = mD3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &mRenderTargetView );
		pBackBuffer->Release();
		if( FAILED( hr ) )
			return false;

		// Create depth stencil texture
		if (mIsStencilBuffer)
		{
			D3D11_TEXTURE2D_DESC descDepth;
			ZeroMemory( &descDepth, sizeof(descDepth) );
			descDepth.Width = mBackBufferWidth;
			descDepth.Height = mBackBufferHeight;
			descDepth.MipLevels = 1;
			descDepth.ArraySize = 1;
			descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			descDepth.SampleDesc.Count = 1;
			descDepth.SampleDesc.Quality = 0;
			descDepth.Usage = D3D11_USAGE_DEFAULT;
			descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			descDepth.CPUAccessFlags = 0;
			descDepth.MiscFlags = 0;

			ID3D11Texture2D* pDepthStencil;
			hr = mD3dDevice->CreateTexture2D( &descDepth, nullptr, &pDepthStencil );
			if( FAILED( hr ) )
				return false;
			// Create the depth stencil view
			DECL_ZERO(D3D11_DEPTH_STENCIL_VIEW_DESC, descDSV);

			descDSV.Format = descDepth.Format;
			descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			descDSV.Texture2D.MipSlice = 0;
			hr = mD3dDevice->CreateDepthStencilView( pDepthStencil, &descDSV, &mDepthStencilView );
			pDepthStencil->Release();
			if( FAILED( hr ) )
				return false;
			mImmediateContext->OMSetRenderTargets( 1, &mRenderTargetView, mDepthStencilView );
		}	

		// Setup the viewport
		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)mBackBufferWidth;
		vp.Height = (FLOAT)mBackBufferHeight;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		mImmediateContext->RSSetViewports( 1, &vp );

		mSysConstBuffer.Setup(mD3dDevice);

		mResourceFactory->Setup();
		return true;
	}

	void D3d11Driver::SetShaderProgram(GPUProgram* program)
	{
		D3d11GPUProgram* d11program = convert<D3d11GPUProgram>(program);
		if(d11program->GetVertexShader())
		{
			ID3D11VertexShader* vs = d11program->GetVertexShader()->GetShader();
			mImmediateContext->VSSetShader(vs, NULL, 0);
		}
		if(d11program->GetPixelShader())
		{
			ID3D11PixelShader* ps = d11program->GetPixelShader()->GetShader();
			mImmediateContext->PSSetShader(ps, NULL, 0);
		}
	}

	void D3d11Driver::Draw(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, InputLayout* layout)
	{
		D3d11VertexBuffer* d11vertex = convert<D3d11VertexBuffer>(vertexBuffer);
		D3d11IndexBuffer* d11index = convert<D3d11IndexBuffer>(indexBuffer);
		D3d11InputLayout* d11layout = convert<D3d11InputLayout>(layout);

		// Set primitive topology
		//mImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

		if (nullptr != d11layout)
		{
			mImmediateContext->IASetInputLayout(d11layout->GetLayout());
		}
		if (nullptr != d11vertex)
		{
			UINT stride = (UINT)d11vertex->GetStrides();
			UINT offset = 0;
			ID3D11Buffer* bf = d11vertex->GetBuffer();
			mImmediateContext->IASetVertexBuffers(0, 1, &bf, &stride, &offset);
		}
		if (nullptr != d11index)
		{
			mImmediateContext->IASetIndexBuffer(d11index->GetBuffer(), d3d11convert::to(d11index->GetFormat()), 0);
		}
		if (nullptr != d11index)
		{
			mImmediateContext->DrawIndexed( d11index->GetCount(), 0, 0 );
		}
		else if (nullptr != d11vertex)
		{
			mImmediateContext->Draw(d11vertex->GetCount(), 0);
		}
	}

	void D3d11Driver::DrawBegin()
	{

		//// Setup the viewport
		//D3D11_VIEWPORT vp;
		//vp.Width = (FLOAT)mBackBufferWidth;
		//vp.Height = (FLOAT)mBackBufferHeight;
		//vp.MinDepth = 0.0f;
		//vp.MaxDepth = 1.0f;
		//vp.TopLeftX = 0;
		//vp.TopLeftY = 0;
		//mImmediateContext->RSSetViewports( 1, &vp );

		float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
		mImmediateContext->ClearRenderTargetView( mRenderTargetView, ClearColor );
		mImmediateContext->ClearDepthStencilView( mDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
	}
	void D3d11Driver::DrawEnd()
	{
		mSwapChain->Present( 0, 0 );
	}
	void D3d11Driver::Release()
	{
		if (nullptr != mResourceFactory)
		{
			mResourceFactory->Release();
			shh_delete mResourceFactory;
			mResourceFactory = nullptr;
		}	

		D3d11Common::DeleteCOMptr(mRenderTargetView);
		D3d11Common::DeleteCOMptr(mDepthStencilView);
		D3d11Common::DeleteCOMptr(mVertexShader);
		D3d11Common::DeleteCOMptr(mPixelShader);
		D3d11Common::DeleteCOMptr(mVertexLayout);

		D3d11Common::DeleteCOMptr(mD3dDevice);
		D3d11Common::DeleteCOMptr(mImmediateContext);
		D3d11Common::DeleteCOMptr(mSwapChain);



		mSysConstBuffer.Release();
	}

	ResourceFactory* D3d11Driver::GetResourceFactory() const
	{
		return (ResourceFactory*)mResourceFactory;
	}

	void D3d11Driver::UpdateConstBuffer_Camera(const CBufferCamera& buffer)
	{
		mSysConstBuffer.UpdateConstBuffer_Camera(buffer, mImmediateContext);
	}

	void D3d11Driver::UpdateConstBuffer_Object(const CBufferObject& buffer)
	{
		mSysConstBuffer.UpdateConstBuffer_Object(buffer, mImmediateContext);
	}
}
#endif
