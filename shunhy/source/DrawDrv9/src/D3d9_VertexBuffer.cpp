#include "D3d9_VertexBuffer.h"
#if __Renderer_d3d9__
namespace Shh
{
	D3d9VertexBuffer::D3d9VertexBuffer(IDirect3DVertexBuffer9* vertex_buffer, SourceUsage usage)
		:D3d9Buffer(usage)
	{
		mVertexBuffer = vertex_buffer;
	}

	D3d9VertexBuffer::~D3d9VertexBuffer()
	{
		_release();
	}
	void D3d9VertexBuffer::Release()
	{
		D3d9Buffer::Release();
		_release();
	}

	SourceUsage D3d9VertexBuffer::GetBufferUsage() const
	{
		return mBufferUsage;
	}

	void D3d9VertexBuffer::TransformUsage(SourceUsage buffer_usage, DWORD& vertex_usage, D3DPOOL& pool_type)
	{
		switch(buffer_usage)
		{
		case BufferUsageImmutable:
			{
				pool_type = D3DPOOL_DEFAULT;
				vertex_usage = D3DUSAGE_WRITEONLY;
			}
			break;
		case BufferUsageDynamic:
			{
				//如果数据需要高频率更新（不断的Lock, Unlock），也需要使用D3DPOOL_DEFAULT，同时使用D3DUSAGE_DYNAMIC标记。这意味着此资源会被创建在AGP Aperture中。
				//例子：使用CPU进行物理运算的粒子系统、使用CPU计算蒙皮的骨骼动画。
				pool_type = D3DPOOL_DEFAULT;
				vertex_usage = D3DUSAGE_WRITEONLY;
			}
			break;
		case BufferUsageStaging:
			{
				pool_type = D3DPOOL_MANAGED;
				vertex_usage = 0;
			}
			break;
		default:	//BufferUsageDefault
			{
				pool_type = D3DPOOL_MANAGED;
				vertex_usage = D3DUSAGE_WRITEONLY;
			}
			break;
		}
	}
}

#endif
