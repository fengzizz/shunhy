#pragma once
#include "IndexBuffer.h"
#include "D3d11_Common.h"
#include "D3d11_Buffer.h"
namespace Shh
{
	class D3d11IndexBuffer : public D3d11Buffer, public IndexBuffer 
	{
		__Super(IndexBuffer)
	public: 
		virtual bool Valid() const;

		D3d11IndexBuffer(ID3D11Buffer* buffer, IndexBufferFormat index_format, SourceUsage usage, size_t strides, size_t count);
		virtual ~D3d11IndexBuffer();
	protected:
	};
}