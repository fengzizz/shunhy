#ifndef __D3D9COMMON_H__
#define __D3D9COMMON_H__
#include <d3d9.h>
#include <d3dx9.h>
#include "DrawDrvConfig.h"
#include "Debug.h"

namespace Shh
{
	class D3d9Driver;
	class D3d9Buffer;
	class D3d9Vertexbuffer;
	class D3d9IndexBuffer;
	class D3d9GpuCRegBuffer;
	class D3d9Texture;
	class D3d9Texture1D;
	class D3d9Texture2D;
	class D3d9TextureCube;
	class D3d9InputLayout;
	class D3d9Shader;
	class D3d9VertexShader;
	class D3d9PixelShader;
	class D3d9ViewPort;

	class D3d9ResourceFactory;



	class D3d9Common
	{
	public:
		static void ReleaseCOM(IUnknown* inter_face);//释放com端口

		template<typename T>
		static void DeleteCOMptr(T& inter_face);//释放com端口，并把inter_face置为空
	};
	inline void D3d9Common::ReleaseCOM(IUnknown* inter_face)
	{
		if (inter_face)
		{		
			inter_face->Release();
		}

	}
	template<typename T>
	inline void D3d9Common::DeleteCOMptr(T& inter_face)
	{
		ReleaseCOM(inter_face);
		inter_face = nullptr;
		//c_assert(0);//警告传入的inter_face是个右值
	}


	class GetD3d9RenderDriver
	{
	public:
		GetD3d9RenderDriver(D3d9Driver* driver);
		virtual ~GetD3d9RenderDriver(){}
		D3d9Driver* GetD3d9Driver() const;//virtual
	protected:
		D3d9Driver* mDriver;
	};
	inline GetD3d9RenderDriver::GetD3d9RenderDriver(D3d9Driver* driver)
	{
		mDriver = driver;
	}
	inline D3d9Driver* GetD3d9RenderDriver::GetD3d9Driver() const
	{
		return mDriver;
	}
}

#endif //__D3D9COMMON_H__
