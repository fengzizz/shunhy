#pragma once
#include "VertexBuffer.h"
#include "D3d11_Common.h"
#include "D3d11_Buffer.h"
namespace Shh
{
	class D3d11VertexBuffer : public VertexBuffer, public D3d11Buffer//
	{
	public: 
		virtual bool Valid() const;

		D3d11VertexBuffer(ID3D11Buffer* buffer, SourceUsage usage, size_t strides, size_t count);

		virtual ~D3d11VertexBuffer();
	};
}