#include "D3d9_ResourceFactory.h"
#include "D3d9_Driver.h"
#include "D3d9_VertexBuffer.h"
#include "D3d9_IndexBuffer.h"
#include "D3d9_VertexShader.h"
#include "D3d9_PixelShader.h"
#include "D3d9_Shader.h"
#if __Renderer_d3d9__
namespace Shh
{

	D3d9ResourceFactory::D3d9ResourceFactory(D3d9Driver* driver)
		:GetD3d9RenderDriver(driver)
	{
	}
	D3d9ResourceFactory::~D3d9ResourceFactory()
	{

	}
	void D3d9ResourceFactory::Release()
	{

	}

	void D3d9ResourceFactory::CreateVertexBuffer(const pointer data, size_t strides, size_t count, SourceUsage usage, OUT VertexBuffer** vertex_buffer)
	{
		shh_assert(data != nullptr);
		shh_assert(*vertex_buffer == nullptr);

		DWORD vertex_usage;
		D3DPOOL pool_type;
		D3d9VertexBuffer::TransformUsage(usage, vertex_usage, pool_type);
		IDirect3DVertexBuffer9* vb = nullptr;
		if (SUCCEEDED(mDriver->GetD3d9Device()->CreateVertexBuffer(length, vertex_usage, 0, pool_type, &vb, nullptr)))
		{
			void* pVertices = nullptr;
			if (SUCCEEDED(vb->Lock(0, length, (void**)&pVertices, 0)))
			{
				memcpy(pVertices, data, length);			
				vb->Unlock();
				(*vertex_buffer) = shh_new D3d9VertexBuffer(vb, usage);
			}
			else
			{
				vb->Release();
				(*vertex_buffer) = nullptr;
			}
		}
		else
		{
			(*vertex_buffer) = nullptr;
		}
		shh_assert(data != nullptr);
	}
	void D3d9ResourceFactory::CreateIndexBuffer(const pointer data, IndexBufferFormat index_format, size_t count, SourceUsage usage, OUT IndexBuffer** index_buffer)
	{
		shh_assert(data != nullptr);
		shh_assert(*index_buffer == nullptr);
		DWORD index_usage;
		D3DPOOL pool_type;
		D3d9IndexBuffer::TransformUsage(usage, index_usage, pool_type);
		IDirect3DIndexBuffer9* ib = nullptr;
		D3DFORMAT format = (IBF_UINT16 == index_format) ? D3DFMT_INDEX16 : D3DFMT_INDEX32;
		//创建索引缓冲区
		if(SUCCEEDED(mDriver->GetD3d9Device()->CreateIndexBuffer(length, index_usage, format, pool_type, &ib, nullptr)))
		{		
			//填充顶点缓冲区
			VOID* pIndices;
			if( SUCCEEDED(ib->Lock(0, length, (void**)&pIndices, 0)))
			{
				memcpy(pIndices, data, length);
				ib->Unlock();
				(*index_buffer) = shh_new D3d9IndexBuffer(ib, usage, index_format);
			}
			else
			{
				ib->Release();
				(*index_buffer) = nullptr;
			}
		}
		else
		{
			(*index_buffer) = nullptr;
		}

		shh_assert(data != nullptr);
	}
	void D3d9ResourceFactory::CreateVertexShader(const U8String& name, const U8String& shader, const U8String& entry_point, VertexShader** vertex_shader)
	{
		shh_assert(0);
	}

	void D3d9ResourceFactory::CreatePixelShader(const U8String& name, const U8String& shader, const U8String& entry_point, PixelShader** pixel_shader)
	{
		shh_assert(0);
	}

}

#endif
