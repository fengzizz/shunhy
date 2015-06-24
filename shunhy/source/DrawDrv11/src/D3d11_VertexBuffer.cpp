#include "D3d11_VertexBuffer.h"
#if __Renderer_d3d11__
namespace Shh
{
	D3d11VertexBuffer::D3d11VertexBuffer(ID3D11Buffer* buffer, SourceUsage usage, size_t strides, size_t count)
		:D3d11Buffer(buffer), VertexBuffer(usage, strides, count)
	{
		mBufferUsage = usage;
	}

	D3d11VertexBuffer::~D3d11VertexBuffer()
	{
		//Release();
	}

	bool D3d11VertexBuffer::Valid() const
	{
		return IsValid();
	}
}
#endif
