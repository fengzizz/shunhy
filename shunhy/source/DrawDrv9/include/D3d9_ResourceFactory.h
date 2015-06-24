#pragma once
#include "D3d9_Common.h"
#include "ResourceFactory.h"
//
// 
//

namespace Shh
{

	class D3d9ResourceFactory : public ResourceFactory, public GetD3d9RenderDriver
	{
	public:
		D3d9ResourceFactory(D3d9Driver* driver);
		virtual void CreateVertexBuffer(const pointer data, size_t strides, size_t count, SourceUsage usage, OUT VertexBuffer** vertex_buffer) override;
		virtual void CreateIndexBuffer(const pointer data, IndexBufferFormat index_format, size_t count, SourceUsage usage, OUT IndexBuffer** index_buffer) override;
		virtual void Release() override;
		virtual ~D3d9ResourceFactory();
	};
}