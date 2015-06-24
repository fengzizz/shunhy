#pragma once
#include "D3d11_Common.h"
#include "ResourceFactory.h"
//
// 
//

namespace Shh
{

	class D3d11ResourceFactory : public ResourceFactory, public GetD3d11RenderDriver
	{
	public:
		D3d11ResourceFactory(D3d11Driver* driver);

		virtual void CreateVertexBuffer(const VertexBufferData& data, OUT VertexBuffer** vertex_buffer) override;

		virtual void CreateIndexBuffer(const IndexBufferData& data, OUT IndexBuffer** index_buffer) override;

		virtual void CreateInputLayout(const InputElements& elems, const void *shader_byte_code, size_t byte_code_len, InputLayout** input_layout) override;
		
		virtual void CreateGPUProgram(const U8String& name, const U8String& vertexShader, const U8String& pixelShader, OUT GPUProgram** program, OUT CompileMessageList& message_list) override;
		

		virtual bool LoadTexture(const pointer src_data, size_t src_len, const ImageLoadInfo* info, Texture** texture) override;

		virtual void DestroyRenderResource(VertexBuffer* resource);
		virtual void DestroyRenderResource(IndexBuffer* resource);
		virtual void DestroyRenderResource(InputLayout* resource);
		virtual void DestroyRenderResource(GPUProgram* resource);
		virtual void DestroyRenderResource(Texture* resource);

		virtual void Release() override;

		virtual void Setup();
		virtual ~D3d11ResourceFactory();

	private:		
		void createVertexShader(const U8String& code, const U8String& entry_point, OUT D3d11VertexShader** vertex_shader, OUT CompileMessageList& message_list);		
		void createPixelShader(const U8String& code, const U8String& entry_point,  OUT D3d11PixelShader** pixel_shader, OUT CompileMessageList& message_list);
		static void reflectShaderParamters(ID3DBlob* code_blob, D3d11Shader* shader);

		ID3DBlob* mEmptyVsBlob;
	};
}