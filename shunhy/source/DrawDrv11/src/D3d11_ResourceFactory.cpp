#include <regex>
#include <algorithm>

#if __Renderer_d3d11__
#include <D3Dcompiler.h>
#endif
#include "Core/FixArray.h"
#include "Core/Convert.h"
#include "Core/StringUtility.h"
#include "D3d11_Utility.h"
#include "D3d11_ResourceFactory.h"
#include "D3d11_Driver.h"
#include "D3d11_VertexBuffer.h"
#include "D3d11_IndexBuffer.h"
#include "D3d11_VertexShader.h"
#include "D3d11_PixelShader.h"
#include "D3d11_CustomBuffer.h"
#include "D3d11_GPUProgram.h"
#include "D3d11_Shader.h"
#include "D3d11_InputLayout.h"
#include "D3d11_Texture.h"


#if __Renderer_d3d11__
#include <D3Dcompiler.h>
#define ELEM_COUNT 8

namespace Shh
{
	static LPCSTR VSEntryPoint = "VSMain";
	static LPCSTR PSEntryPoint = "PSMain";




	void parseError(ID3DBlob* error_blob, OUT CompileMessageList& message_list)
	{
		//shh_log((char*)error_blob->GetBufferPointer());

		message_list.push_back(CompileMessage());

		U8String emsg = (char*)error_blob->GetBufferPointer();
		//e.g. E:\SourceCode\VertexShader(108,21): warning X3206: implicit truncation of vector type

		static  const std::regex patternLineInfo("\\([0-9]+,[0-9]+\\)\\:");//("\\(?=([0-9]+),?=([0-9])+\\)");
		std::smatch result;//std:: match_results<std::string::const_iterator>
		bool valid = std::regex_search(emsg, result, patternLineInfo);//result,

		if (result.size() > 0)
		{
			U8String tmp = result[0];
			std::vector<U8String> svalues;
			static const U8String delims = "(,):";
			utility::split(svalues, tmp, delims);
			if (svalues.size() == 2)
			{
				if (utility::parseInt(svalues[0], message_list.back().LineOn) && utility::parseInt(svalues[1], message_list.back().Position))
				{			
					message_list.back().Title = result.prefix();
					message_list.back().Message = result.suffix();
					utility::trim(message_list.back().Title);
					utility::trim(message_list.back().Message);
					return;
				}
			}	
		}
		// if false.
		message_list.back().Message = emsg;
		message_list.back().LineOn = Invalid_Index;
		message_list.back().Position = Invalid_Index;

	}


	D3d11ResourceFactory::D3d11ResourceFactory(D3d11Driver* driver)
		:GetD3d11RenderDriver(driver)
	{
	}
	D3d11ResourceFactory::~D3d11ResourceFactory()
	{

	}
	void D3d11ResourceFactory::Release()
	{
		D3d11Common::DeleteCOMptr(mEmptyVsBlob);
	}

	void D3d11ResourceFactory::Setup()
	{
		String emptyvs = "float4 vs(float4 pos : POSITION) : SV_POSITION { return pos;}";

		HRESULT hr = S_OK;
		const D3D10_SHADER_MACRO* pDefines = NULL;
		ID3DInclude* pInclude = NULL;
		ID3DBlob* error_blob = NULL;

		DWORD shader_flags = SHADER_COMPILE_FLAG;
		hr = D3DCompile(emptyvs.c_str(), emptyvs.size(), "PixelShader", pDefines, pInclude, 
			"vs", "vs_4_0", shader_flags, 0, &mEmptyVsBlob, &error_blob);

		D3d11Common::ReleaseCOM(error_blob);
	}
	void D3d11ResourceFactory::CreateVertexBuffer(const VertexBufferData& data, OUT VertexBuffer** vertex_buffer)
	{
		shh_assert(*vertex_buffer == nullptr);

		DECL_ZERO(D3D11_BUFFER_DESC, bd);

		size_t vertexStrides = CalculateVertexStrides(data.vertex.vertexComponents);
		size_t vertexBufferSize = vertexStrides * data.vertexCount;
		bd.Usage = d3d11convert::to(data.usage);
		bd.ByteWidth = (UINT)vertexBufferSize;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		DECL_ZERO(D3D11_SUBRESOURCE_DATA, InitData);
		fixarray<uchar> bufferData(vertexBufferSize);
		CopyVertexDataToGraphicBuffer(bufferData.get(), data, vertexStrides);

		InitData.pSysMem = bufferData.get();

		ID3D11Buffer* buffer = nullptr;
		HRESULT hr = mDriver->GetD3d11Device()->CreateBuffer( &bd, &InitData, &buffer );
		if (SUCCEEDED(hr))
		{
			(*vertex_buffer) = shh_new D3d11VertexBuffer(buffer, data.usage, vertexStrides, data.vertexCount);
		}
		else
		{
			(*vertex_buffer) = nullptr;
		}
	}
	void D3d11ResourceFactory::CreateIndexBuffer(const IndexBufferData& data, OUT IndexBuffer** index_buffer)
	{
		shh_assert(*index_buffer == nullptr);

		int strides = data.format.getSize();

		DECL_ZERO(D3D11_BUFFER_DESC, bd);

		bd.Usage = d3d11convert::to(data.usage);
		bd.ByteWidth = strides * data.indexCount;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		DECL_ZERO(D3D11_SUBRESOURCE_DATA, InitData);

		InitData.pSysMem = data.stream;
		ID3D11Buffer* buffer = nullptr;
		HRESULT hr = mDriver->GetD3d11Device()->CreateBuffer( &bd, &InitData, &buffer);
		if (SUCCEEDED(hr))
		{
			(*index_buffer) = shh_new D3d11IndexBuffer(buffer, data.format, data.usage, strides, data.indexCount);
		}
		else
		{
			(*index_buffer) = nullptr;
		}
	}

	void D3d11ResourceFactory::CreateGPUProgram(const U8String& name, const U8String& vertexShader, const U8String& pixelShader, OUT GPUProgram** program, OUT CompileMessageList& message_list)
	{
		D3d11VertexShader* vs = nullptr;
		D3d11PixelShader* ps = nullptr;
		//D3d11CustomBuffer* cb = shh_new D3d11CustomBuffer();
		shader_log("");
		shader_log("build shader: %s\n", name.c_str()); 
		createVertexShader(vertexShader, VSEntryPoint, &vs, message_list);
		createPixelShader(pixelShader, PSEntryPoint, &ps, message_list);
		shader_log("build shader end(%s).\n\n", name.c_str());

		if (vs && ps)
		{
			D3d11GPUProgram* program11 = shh_new D3d11GPUProgram(name, vs, ps);
			*program = program11;
		}
		else
		{
			//cb->Release();
			//shh_delete cb;
			//cb = nullptr;
		}
	}


	void D3d11ResourceFactory::CreateInputLayout(const InputElements& elems, const void *shader_byte_code, size_t byte_code_len, OUT InputLayout** input_layout)
	{
		shh_assert(*input_layout == nullptr);
		if (!elems.size())
		{
			(*input_layout) = shh_new D3d11InputLayout(elems, NULL, mDriver);
			return;
		}
		ID3D11InputLayout* layout = NULL;

		fixarray<D3D11_INPUT_ELEMENT_DESC> d3d11_elems(elems.size());
		for (size_t x = 0; x < elems.size(); ++x)
		{
			D3d11InputLayout::TransInputElement(elems[x], d3d11_elems[x]);
		}

		if (nullptr == shader_byte_code)
		{
			shader_byte_code = mEmptyVsBlob->GetBufferPointer();
			byte_code_len = mEmptyVsBlob->GetBufferSize();
		}
		HRESULT hr = mDriver->GetD3d11Device()->CreateInputLayout(d3d11_elems.get(), elems.size(), shader_byte_code, byte_code_len, &layout);
		if (SUCCEEDED(hr))
		{
			(*input_layout) = shh_new D3d11InputLayout(elems, layout, mDriver);
		}
		else
		{
			(*input_layout) = nullptr; 
		}
		

	}
	bool D3d11ResourceFactory::LoadTexture(const pointer src_data, size_t src_len, const ImageLoadInfo* info, OUT Texture** texture)
	{
		return false;
	}


	template<typename _T, typename _T2>
	void destroyRenderResource(_T2* resource)
	{
		_T* d3d11resource = static_cast<_T*>(resource);
		d3d11resource->Release();
	}

	void D3d11ResourceFactory::DestroyRenderResource(VertexBuffer* resource)
	{
		destroyRenderResource<D3d11VertexBuffer>(resource);
	}
	void D3d11ResourceFactory::DestroyRenderResource(IndexBuffer* resource)
	{
		destroyRenderResource<D3d11IndexBuffer>(resource);
	}
	void D3d11ResourceFactory::DestroyRenderResource(InputLayout* resource)
	{
		destroyRenderResource<D3d11InputLayout>(resource);
	}
	void D3d11ResourceFactory::DestroyRenderResource(GPUProgram* resource)
	{
		destroyRenderResource<D3d11GPUProgram>(resource);
	}
	void D3d11ResourceFactory::DestroyRenderResource(Texture* resource)
	{
		destroyRenderResource<D3d11Texture>(resource);
	}


	void D3d11ResourceFactory::createVertexShader(const U8String& code, const U8String& entry_point, OUT D3d11VertexShader** vertex_shader, OUT CompileMessageList& message_list)
	{
		HRESULT hr = S_OK;
		const D3D_SHADER_MACRO* pDefines = NULL;
		ID3DInclude* pInclude = NULL;
		ID3DBlob* code_blob = NULL;
		ID3DBlob* error_blob = NULL;

		DWORD shader_flags = SHADER_COMPILE_FLAG;

		hr = D3DCompile(code.c_str(), code.size(),"VertexShader", pDefines, pInclude, 
			entry_point.c_str(), "vs_4_0", shader_flags, 0, &code_blob, &error_blob);
		if (error_blob)
		{
			parseError(error_blob, message_list);
		}
		if (SUCCEEDED(hr) && NULL != code_blob)
		{
			ID3D11VertexShader* v_shader = NULL;
			hr = mDriver->GetD3d11Device()->CreateVertexShader(code_blob->GetBufferPointer(),
				code_blob->GetBufferSize(), NULL, &v_shader);
			
			if (SUCCEEDED(hr))
			{
				D3d11VertexShader* vertex_shader11 = shh_new D3d11VertexShader(v_shader, nullptr);
				(*vertex_shader) = vertex_shader11;
				reflectShaderParamters(code_blob, vertex_shader11);
			}
			else
			{
				vertex_shader = nullptr;
			}
		} 
		else
		{
			vertex_shader = nullptr;
		}
		D3d11Common::ReleaseCOM(code_blob);
		D3d11Common::ReleaseCOM(error_blob);
	}
	void D3d11ResourceFactory::createPixelShader(const U8String& code, const U8String& entry_point, OUT D3d11PixelShader** pixel_shader, OUT CompileMessageList& message_list)
	{
		HRESULT hr = S_OK;
		const D3D10_SHADER_MACRO* pDefines = NULL;
		ID3DInclude* pInclude = NULL;
		ID3DBlob* code_blob = NULL;
		ID3DBlob* error_blob = NULL;

		DWORD shader_flags = SHADER_COMPILE_FLAG;
		hr = D3DCompile(code.c_str(), code.size(), "PixelShader", pDefines, pInclude, 
			entry_point.c_str(), "ps_4_0", shader_flags, 0, &code_blob, &error_blob);
		if (error_blob)
		{
			parseError(error_blob, message_list);
		}
		if (SUCCEEDED(hr))
		{
			ID3D11PixelShader* p_shader = NULL;
			hr = mDriver->GetD3d11Device()->CreatePixelShader(code_blob->GetBufferPointer(),
				code_blob->GetBufferSize(), NULL, &p_shader);
			
			if (SUCCEEDED(hr))
			{
				D3d11PixelShader* pixel_shader11 = shh_new D3d11PixelShader(p_shader, nullptr);
				(*pixel_shader) = pixel_shader11;
				reflectShaderParamters(code_blob, pixel_shader11);
			}
			else
			{
				pixel_shader = nullptr;
			}
		}
		else
		{
			pixel_shader = nullptr;
		}
		D3d11Common::ReleaseCOM(code_blob);
		D3d11Common::ReleaseCOM(error_blob);
	}
	void D3d11ResourceFactory::reflectShaderParamters(ID3DBlob* code_blob, D3d11Shader* shader)
	{
		shh_assert(code_blob != nullptr);
		shh_assert(shader != nullptr);
		ID3D11ShaderReflection* pReflector = NULL; 
		HRESULT hr = D3DReflect( code_blob->GetBufferPointer(), code_blob->GetBufferSize(), IID_ID3D11ShaderReflection, (LPVOID*)&pReflector); 
		shh_assert(SUCCEEDED(hr));
		
		shader->Bind(pReflector);
	}
}
#endif
