#include "D3d9_IndexBuffer.h"
#if __Renderer_d3d9__
namespace Shh
{
	D3d9IndexBuffer::D3d9IndexBuffer(IDirect3DIndexBuffer9* index_buffer, SourceUsage usage, 
									 IndexBufferFormat index_format)
		: D3d9Buffer(usage)
		, mIndexBuffer(index_buffer)
		, mIndexFormat(index_format)
	{
	}

	D3d9IndexBuffer::~D3d9IndexBuffer()
	{
		_release();
	}
	void D3d9IndexBuffer::Release()
	{
		D3d9Buffer::Release();
		_release();
	}
	SourceUsage D3d9IndexBuffer::GetBufferUsage() const
	{
		return mBufferUsage;
	}
	IndexBufferFormat D3d9IndexBuffer::GetIndexBufferFormat() const
	{
		return mIndexFormat;
	}

	void D3d9IndexBuffer::TransformUsage(SourceUsage buffer_usage, DWORD& index_usage, D3DPOOL& pool_type)
	{
		switch(buffer_usage)
		{
		case BufferUsageImmutable:
			{
				pool_type = D3DPOOL_DEFAULT;
				index_usage = D3DUSAGE_WRITEONLY;
			}
			break;
		case BufferUsageDynamic:
			{
				//如果数据需要高频率更新（不断的Lock, Unlock），也需要使用D3DPOOL_DEFAULT，同时使用D3DUSAGE_DYNAMIC标记。这意味着此资源会被创建在AGP Aperture中。
				pool_type = D3DPOOL_DEFAULT;
				index_usage = D3DUSAGE_WRITEONLY;
			}
			break;
		case BufferUsageStaging:
			{
				pool_type = D3DPOOL_MANAGED;
				index_usage = 0;
			}
			break;
		default:	//BufferUsageDefault
			{
				pool_type = D3DPOOL_MANAGED;
				index_usage = D3DUSAGE_WRITEONLY;
			}
			break;
		}
	}
}
#endif
