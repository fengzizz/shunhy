#include <d3d11shader.h>
#include "D3d11_VertexShader.h"
#include "D3d11_PixelShader.h"
#include "D3d11_CustomBuffer.h"
#include "D3d11_Driver.h"
#include "D3d11_GPUProgram.h"
namespace Shh
{
	D3d11GPUProgram::D3d11GPUProgram(const U8String& name, D3d11VertexShader* vs, D3d11PixelShader* ps)
		:GPUProgram(name), mVertexShader(vs), mPixelShader(ps), mClassLinkage(NULL)
	{

	}

	D3d11GPUProgram::~D3d11GPUProgram()
	{
		_release();
	}


	bool D3d11GPUProgram::Valid() const
	{
		return (NULL != mVertexShader);
	}

	void D3d11GPUProgram::Release()
	{
		_release();
	}

	void D3d11GPUProgram::_release()
	{
		if (mVertexShader)
		{
			mVertexShader->Release();
			mVertexShader = nullptr;

		}
		if (mPixelShader)
		{
			mPixelShader->Release();
			mPixelShader = nullptr;
		}

		//if (mCustomBuffer)
		//{
		//	mCustomBuffer->Release();
		//	mCustomBuffer = nullptr;
		//}
	}
	//void D3d11GPUProgram::BuildParamers(ID3D11ShaderReflection* pReflector)
	//{
	//	D3D11_SHADER_DESC desc; 
	//	pReflector->GetDesc(&desc); 
	//	shader_log("Version: %d\n", desc.Version); 
	//	shader_log("Creator: %s\n", desc.Creator); 
	//	shader_log("ConstantBuffers: %d\n", desc.ConstantBuffers); 
	//	shader_log("BoundResources: %d\n", desc.BoundResources); 
	//	shader_log("InputParameters: %d\n", desc.InputParameters); 
	//	shader_log("OutputParameters: %d\n", desc.OutputParameters); 
	//	shader_log("InstructionCount: %d\n", desc.InstructionCount); 
	//	shader_log("TempRegisterCount: %d\n", desc.TempRegisterCount); 
	//	shader_log("TempArrayCount: %d\n", desc.TempArrayCount); 
	//	shader_log("DefCount: %d\n", desc.DefCount); 
	//	shader_log("DclCount: %d\n", desc.DclCount); 
	//	shader_log("FloatInstructionCount: %d\n", desc.FloatInstructionCount); 
	//	shader_log("IntInstructionCount: %d\n", desc.IntInstructionCount); 
	//	shader_log("UintInstructionCount: %d\n", desc.UintInstructionCount); 
	//	shader_log("StaticFlowControlCount: %d\n", desc.StaticFlowControlCount); 
	//	shader_log("DynamicFlowControlCount: %d\n", desc.DynamicFlowControlCount); 

	//	D3d11SystemBuffer& system_buffer = D3d11Driver::GetSingletonPtr()->GetD3d11SystemBuffer();
	//	D3D11_SHADER_INPUT_BIND_DESC resDesc; 

	//	for (size_t i = 0; i < desc.BoundResources; i++) 
	//	{ 
	//		pReflector->GetResourceBindingDesc(i, &resDesc); 
	//		switch(resDesc.Type)
	//		{
	//		case D3D_SIT_CBUFFER:
	//			{
	//				D3d11ConstBuffer* br = shh_new D3d11ConstBuffer();
	//				br->Set(resDesc, pReflector);
	//				_addConstBuffer(br);	
	//			}
	//			break;
	//		case D3D_SIT_TEXTURE:
	//			{
	//				shh_warnning("unfulfilment (D3D_SIT_TEXTURE)");
	//				//br = n_new D3d11BoundTexture();
	//			}
	//			break;
	//		case D3D_SIT_SAMPLER:
	//			{
	//				shh_warnning("unfulfilment (D3D_SIT_SAMPLER)");
	//				//br = n_new D3d11BoundSampler();
	//			}
	//			break;
	//		default:
	//			{
	//				shader_log("Unknown Resource Type.");
	//				shader_log("Resource %d:\n", i); 
	//				shader_log("\tName: %s\n", resDesc.Name); 
	//				shader_log("\tType: %d\n", resDesc.Type); 
	//				shader_log("\tBindPoint: %d\n", resDesc.BindPoint); 
	//				shader_log("\tBindCount: %d\n", resDesc.BindCount); 
	//				shader_log("\tReturnType: %d\n", resDesc.ReturnType); 
	//			}
	//			break;
	//		}
	//	} 
	//	_buildCustomParamers();
	//}


	//void D3d11GPUProgram::setCustomVariable(const HString& name, const pointer data)
	//{
	//	const custom_variable* var_ptr = _findCustomVar(name);
	//	if (var_ptr)
	//	{
	//		switch(var_ptr->info->type)
	//		{
	//		case SP_MATRIX44:
	//			{
	//				*(mVarBlock.As<Matrix4>(var_ptr->block_offset)) = *((Matrix4*)data);
	//			}
	//			break;
	//		case SP_FLOAT:
	//		case SP_INT:
	//			{
	//				XMemory::CopySizeT1(data, mVarBlock.GetPtr(var_ptr->block_offset));
	//			}
	//			break;

	//		case SP_FLOAT2:
	//			{
	//				XMemory::CopySizeT2(data, mVarBlock.GetPtr(var_ptr->block_offset));
	//			}
	//			break;
	//		case SP_FLOAT3:
	//			{
	//				XMemory::CopySizeT3(data, mVarBlock.GetPtr(var_ptr->block_offset));
	//			}
	//			break;
	//		case SP_FLOAT4:
	//			{
	//				XMemory::CopySizeT4(data, mVarBlock.GetPtr(var_ptr->block_offset));
	//			}
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}

	//void D3d11GPUProgram::_addConstBuffer(D3d11ConstBuffer* buffer)
	//{
	//	shh_assert(nullptr != buffer);
	//	D3d11SystemBuffer& system_buffer = D3d11Driver::GetSingletonPtr()->GetD3d11SystemBuffer();
	//	if (system_buffer.IsSystemConstBuffer(buffer->GetName()))
	//	{
	//		mSystemConstBuffers.push_back(buffer);
	//		return;
	//	}
	//	custom_const_buffer info;
	//	info.const_buffer = buffer;
	//	mCustomConstBuffers.push_back(info);
	//}

	//void D3d11GPUProgram::_buildCustomParamers()
	//{
	//	int custom_len = 0;

	//	for (size_t i = 0; i < mCustomConstBuffers.size(); ++i)
	//	{
	//		D3d11ConstBuffer::VariableInfos& bindvars =  mCustomConstBuffers[i].const_buffer->GetVariables();
	//		__FOR_EACH_BEGIN(D3d11ConstBuffer::VariableInfos, bindvars, elem)
	//			custom_len += elem->size;
	//		__FOR_EACH_END(elem)
	//	}
	//	mVarBlock.ResizeDefault(custom_len, 0);
	//	int offset = 0;
	//	for (size_t i = 0; i < mCustomConstBuffers.size(); ++i)
	//	{
	//		D3d11ConstBuffer::VariableInfos& bindvars =  mCustomConstBuffers[i].const_buffer->GetVariables();
	//		custom_variables& cvars = mCustomConstBuffers[i].custom_vars;

	//		for (size_t j = 0; j < bindvars.size(); ++j)
	//		{
	//			custom_variable cvar;
	//			cvar.info = &bindvars[j];
	//			cvar.block_offset = offset;
	//			offset += cvar.info->size;
	//			cvars.push_back(cvar);
	//		}
	//	}
	//}

	//const D3d11GPUProgram::custom_variable* D3d11GPUProgram::_findCustomVar(const HString& name) const
	//{
	//	__FOR_EACH_BEGIN(custom_const_buffers, mCustomConstBuffers, elem)
	//		__FOR_EACH_BEGIN(custom_variables, elem->custom_vars, var)
	//		if (var->info->name == name)
	//		{
	//			return &(*var);
	//		}
	//		__FOR_EACH_END(var)
	//			__FOR_EACH_END(elem)
	//			return nullptr;
	//}
}