#pragma once

#include "Core/IRelease.h"
#include "Core/U8String.h"
#include "DrawDrv/DrawDrvDef.h"
#include "DrawDrv/RenderFormat.h"
#include "DrawDrv/RenderData.h"
//

namespace Shh
{
	typedef std::vector<InputElement> InputElements;
	class _Shh_Export ResourceFactory : IRelease//IGetRenderDiver,
	{
	public:
		virtual void CreateVertexBuffer(const VertexBufferData& data, OUT VertexBuffer** vertex_buffer) = 0;
		virtual void CreateIndexBuffer(const IndexBufferData& data, OUT IndexBuffer** index_buffer) = 0;
		virtual void CreateInputLayout(const InputElements& elems, const void *shader_byte_code, size_t byte_code_len, InputLayout** input_layout) = 0;

		virtual void CreateGPUProgram(const U8String& name, const U8String& vertexShader, const U8String& pixelShader, OUT GPUProgram** program, OUT CompileMessageList& message_list) = 0;
		virtual bool LoadTexture(const pointer src_data, size_t src_len, const ImageLoadInfo* info, OUT Texture** texture) = 0;

		virtual void DestroyRenderResource(VertexBuffer* resource) = 0;
		virtual void DestroyRenderResource(IndexBuffer* resource) = 0;
		virtual void DestroyRenderResource(InputLayout* resource) = 0;
		virtual void DestroyRenderResource(GPUProgram* resource) = 0;
		virtual void DestroyRenderResource(Texture* resource) = 0;

		virtual ~ResourceFactory() {};
	};
}