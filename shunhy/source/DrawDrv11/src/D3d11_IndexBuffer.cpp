#include "D3d11_IndexBuffer.h"
#if __Renderer_d3d11__
namespace Shh
{
	D3d11IndexBuffer::D3d11IndexBuffer(ID3D11Buffer* buffer, IndexBufferFormat index_format, SourceUsage usage, size_t strides, size_t count)
		: D3d11Buffer(buffer)
		, super(usage, strides, count)
	{
		mBufferUsage = usage; 
		mFormat = index_format;
	}

	D3d11IndexBuffer::~D3d11IndexBuffer()
	{
		//Release();
	}

	bool D3d11IndexBuffer::Valid() const
	{
		return IsValid();
	}
}
#endif
