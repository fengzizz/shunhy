#include "D3d11_Driver.h"
#include "D3d11_Shader.h"
#if __Renderer_d3d11__
namespace Shh
{
	void D3d11ShaderReflection::Build(ID3D11ShaderReflection* pReflector)
	{
		mCBufferBindings.clear();
		mVariableBindings.clear();
		D3D11_SHADER_DESC desc; 
		pReflector->GetDesc(&desc); 
		shader_log("Version: %d", desc.Version); 
		shader_log("Creator: %s", desc.Creator); 
		shader_log("ConstantBuffers: %d", desc.ConstantBuffers); 
		shader_log("BoundResources: %d", desc.BoundResources); 
		shader_log("InputParameters: %d", desc.InputParameters); 
		shader_log("OutputParameters: %d", desc.OutputParameters); 
		shader_log("InstructionCount: %d", desc.InstructionCount); 
		shader_log("TempRegisterCount: %d", desc.TempRegisterCount); 
		shader_log("TempArrayCount: %d", desc.TempArrayCount); 
		shader_log("DefCount: %d", desc.DefCount); 
		shader_log("DclCount: %d", desc.DclCount); 
		shader_log("FloatInstructionCount: %d", desc.FloatInstructionCount); 
		shader_log("IntInstructionCount: %d", desc.IntInstructionCount); 
		shader_log("UintInstructionCount: %d", desc.UintInstructionCount); 
		shader_log("StaticFlowControlCount: %d", desc.StaticFlowControlCount); 
		shader_log("DynamicFlowControlCount: %d", desc.DynamicFlowControlCount); 

		D3D11_SHADER_INPUT_BIND_DESC resDesc; 

		for (size_t i = 0; i < desc.BoundResources; i++) 
		{ 
			pReflector->GetResourceBindingDesc(i, &resDesc); 
			switch(resDesc.Type)
			{
			case D3D_SIT_CBUFFER:
				{
					shader_log("build const buffer.");
					_buildCBuffer(resDesc, pReflector);
				}
				break;
			case D3D_SIT_TEXTURE:
				{
					shader_log("build texture.");
					_buildCTexture(resDesc, pReflector);
				}
				break;
			case D3D_SIT_SAMPLER:
				{
					shader_log("build sampler.");
					_buildCSampler(resDesc, pReflector);
				}
				break;
			default:
				{
					shader_log("Unknown Resource Type.");
					shader_log("Resource %d:", i); 
					shader_log("\tName: %s", resDesc.Name); 
					shader_log("\tType: %d", resDesc.Type); 
					shader_log("\tBindPoint: %d", resDesc.BindPoint); 
					shader_log("\tBindCount: %d", resDesc.BindCount); 
					shader_log("\tReturnType: %d", resDesc.ReturnType); 
				}
				break;
			}
		} 
	}
	void D3d11ShaderReflection::_buildCBuffer(const D3D11_SHADER_INPUT_BIND_DESC& bind, ID3D11ShaderReflection* pReflector)
	{
		shader_log("\tName: %s", bind.Name); 
		shader_log("\tType: %d", bind.Type); 
		shader_log("\tBindPoint: %d", bind.BindPoint); 
		shader_log("\tBindCount: %d", bind.BindCount); 
		shader_log("\tReturnType: %d", bind.ReturnType); 

		ID3D11ShaderReflectionConstantBuffer * pCBReflector = pReflector->GetConstantBufferByName(bind.Name); 
		D3D11_SHADER_BUFFER_DESC sbDesc; 
		pCBReflector->GetDesc(&sbDesc); 

		shh_assert(0 == strcmp(bind.Name, sbDesc.Name));
		shader_log("\tVariables: %d", sbDesc.Variables); 
		shader_log("\tSize: %d", sbDesc.Size);


		mCBufferBindings.push_back(CBufferBinding());
		mCBufferBindings.back().BindCount = bind.BindCount;
		mCBufferBindings.back().BindPoint = bind.BindPoint;
		mCBufferBindings.back().Size = sbDesc.Size;
		mCBufferBindings.back().Variables = sbDesc.Variables;
		mCBufferBindings.back().Name = sbDesc.Name;


		//HString name = bind.Name;

		//const D3d11SystemBuffer& systemBuffer = D3d11Driver::GetSingletonPtr()->GetD3d11SystemBuffer();

		//if (systemBuffer.IsSystemConstBuffer(name))
		//{
		//	shader_log("\tsystem buffer.");
		//}
		//else
		//{
		//	shader_log("\tcustom buffer.");
		//}

		int bufferIndex = mCBufferBindings.size() - 1;
		for (size_t j = 0; j < sbDesc.Variables; j++) 
		{ 
			ID3D11ShaderReflectionVariable* pVReflector = pCBReflector->GetVariableByIndex(j); 
			D3D11_SHADER_VARIABLE_DESC varDesc; 
			pVReflector->GetDesc(&varDesc);

			// Only parse if variable is used
			if (varDesc.uFlags & D3D_SVF_USED)
			{
				mVariableBindings.push_back(VariableBinding());
				mVariableBindings.back().Name = varDesc.Name;
				mVariableBindings.back().BufferIndex = bufferIndex;
				mVariableBindings.back().StartOffset = varDesc.StartOffset;
				mVariableBindings.back().Size = varDesc.Size;
				shader_log("\t\t\tName:%s, StartOffset: %d, Size: %d", varDesc.Name, varDesc.StartOffset, varDesc.Size); 
			}
		}
	}

	void D3d11ShaderReflection::_buildCTexture(const D3D11_SHADER_INPUT_BIND_DESC& bind, ID3D11ShaderReflection* pReflector)
	{
		shader_log("\tName: %s", bind.Name); 
		shader_log("\tType: %d", bind.Type); 
		shader_log("\tBindPoint: %d", bind.BindPoint); 
		shader_log("\tBindCount: %d", bind.BindCount); 
		shader_log("\tReturnType: %d", bind.ReturnType); 

		mTextureBindings.push_back(TextureBinding());
		mTextureBindings.back().BindCount = bind.BindCount;
		mTextureBindings.back().BindPoint = bind.BindPoint;
		mTextureBindings.back().Name = bind.Name;
	}
	void D3d11ShaderReflection::_buildCSampler(const D3D11_SHADER_INPUT_BIND_DESC& bind, ID3D11ShaderReflection* pReflector)
	{
		shader_log("\tName: %s", bind.Name); 
		shader_log("\tType: %d", bind.Type); 
		shader_log("\tBindPoint: %d", bind.BindPoint); 
		shader_log("\tBindCount: %d", bind.BindCount); 
		shader_log("\tReturnType: %d", bind.ReturnType);

		mSamplerBindings.push_back(SamplerBinding());
		mSamplerBindings.back().BindCount = bind.BindCount;
		mSamplerBindings.back().BindPoint = bind.BindPoint;
		mSamplerBindings.back().Name = bind.Name;
	}


	D3d11Shader::D3d11Shader(ID3D11ClassLinkage* class_linkage)
		: mClassLinkage(class_linkage)
	{

	}
	D3d11Shader::~D3d11Shader()
	{
		_release();
	}

	void D3d11Shader::Bind(ID3D11ShaderReflection* pReflector)
	{
		mReflection.Build(pReflector);
	}

	void D3d11Shader::Release()
	{
		_release();
	}

	void D3d11Shader::_release()
	{
		D3d11Common::DeleteCOMptr(mClassLinkage);
	}
}
#endif
