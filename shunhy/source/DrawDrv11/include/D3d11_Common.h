#ifndef __D3D11COMMON_H__
#define __D3D11COMMON_H__
#include <d3d11.h>
#include <vector>
#include "Core/U8String.h"
#include "Core/Log.h"
#include "DrawDrv/RenderFormat.h"






#if __PRINT_ALL_DEBUG_LOG__
# define __SHADER_LOG__
#endif

#ifdef __SHADER_LOG__
#	define shader_log(fmt, ... ) shh_log(fmt, __VA_ARGS__)
#else
#	define shader_log(fmt, ... )
#endif


#if _DEBUG
#	define SHADER_DEBUG 1
#else
#	define SHADER_DEBUG 0
#endif


#if SHADER_DEBUG
#	define SHADER_COMPILE_FLAG (D3DCOMPILE_SKIP_VALIDATION | D3DCOMPILE_DEBUG)
#else
#	define SHADER_COMPILE_FLAG 0
#endif

#define HRESULT_SUCCEEDED(r) if(!SUCCEEDED(r)) {shh_assert(0);}
namespace Shh
{
	class D3d11Driver;
	class D3d11Buffer;
	class D3d11Vertexbuffer;
	class D3d11IndexBuffer;
	class D3d11Texture;
	class D3d11Texture1D;
	class D3d11Texture2D;
	class D3d11TextureCube;
	class D3d11InputLayout;
	class D3d11Shader;
	class D3d11VertexShader;
	class D3d11PixelShader;
	class D3d11GPUProgram;
	class D3d11ViewPort;
	class D3d11ResourceFactory;
	class D3d11SystemBuffer;


	class D3d11BoundResource;
	class D3d11BoundTexture;
	class D3d11BoundSampler;

	class D3d11ConstBuffer;
	class D3d11CustomBuffer;

	class D3d11Common
	{
	public:
		static void ReleaseCOM(IUnknown* inter_face);//释放com端口

		template<typename T>
		static void DeleteCOMptr(T& inter_face);//释放com端口，并把inter_face置为空
	};
	inline void D3d11Common::ReleaseCOM(IUnknown* inter_face)
	{
		if (inter_face)
		{		
			inter_face->Release();
		}

	}
	template<typename T>
	inline void D3d11Common::DeleteCOMptr(T& inter_face)
	{
		ReleaseCOM(inter_face);
		inter_face = nullptr;
	}

	class D3d11Resource : IRelease
	{
	public:
		virtual ~D3d11Resource();
	};


	class GetD3d11RenderDriver
	{
	public:
		GetD3d11RenderDriver(D3d11Driver* driver);
		virtual ~GetD3d11RenderDriver(){}
		D3d11Driver* GetD3d11Driver() const;
	protected:
		D3d11Driver* mDriver;
	};
	inline GetD3d11RenderDriver::GetD3d11RenderDriver(D3d11Driver* driver)
		:mDriver(driver)
	{;
	}
	inline D3d11Driver* GetD3d11RenderDriver::GetD3d11Driver() const
	{
		return mDriver;
	}
}
#endif //__D3D11COMMON_H__


