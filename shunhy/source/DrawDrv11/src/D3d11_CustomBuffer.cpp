#include <d3d11shader.h>
#include "D3d11_Driver.h"
#include "D3d11_BoundResource.h"
#include "D3d11_CustomBuffer.h"

namespace Shh
{

	EShaderParam _get_param_type(const D3D11_SHADER_TYPE_DESC& pamam_desc)
	{
		EShaderParam spt = SP_UNKNOWN;
		switch(pamam_desc.Class)
		{
		case D3D_SVC_MATRIX_ROWS:
		case D3D_SVC_MATRIX_COLUMNS:
			{
				if (4 == pamam_desc.Columns && 4 == pamam_desc.Rows && D3D10_SVT_FLOAT == pamam_desc.Type)
				{
					spt = SP_MATRIX44;
				}
			}
			break;
		case D3D_SVC_VECTOR:
			{
				if(1 == pamam_desc.Rows && D3D10_SVT_FLOAT == pamam_desc.Type)
				{
					switch(pamam_desc.Columns)
					{
					case 2:
						{
							spt = SP_FLOAT2;
						}
						break;
					case 3:
						{
							spt = SP_FLOAT3;
						}
						break;
					case 4:
						{
							spt = SP_FLOAT4;
						}
						break;
					default:
						break;
					}
				}
			}
			break;
		case D3D_SVC_SCALAR:
			{
				switch(pamam_desc.Type)
				{
				case D3D_SVT_FLOAT:
					{
						spt = SP_FLOAT;
					}
					break;
				case D3D_SVT_INT:
					{
						spt = SP_INT;
					}
					break;
				default:
					break;
				}
			}
		default:
			break;
		}
		return spt;
	}


	D3d11CustomBuffer::D3d11CustomBuffer()
	{

	}

	D3d11CustomBuffer::~D3d11CustomBuffer()
	{
		_release();
	}

	void D3d11CustomBuffer::Release()
	{
		_release();
	}

	void D3d11CustomBuffer::_release()
	{
		mCustomVariables.clear();
		mCustomConstBuffers.clear();
	}
	void D3d11CustomBuffer::BuildParamers(ID3D11ShaderReflection* pReflector)
	{
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
					_buildConstBuffer(resDesc, pReflector);
				}
				break;
			case D3D_SIT_TEXTURE:
				{
					shader_log("build texture.");
					shh_warnning("unfulfilment (D3D_SIT_TEXTURE)");
					//br = n_new D3d11BoundTexture();
				}
				break;
			case D3D_SIT_SAMPLER:
				{
					shader_log("build sampler.");
					shh_warnning("unfulfilment (D3D_SIT_SAMPLER)");
					//br = n_new D3d11BoundSampler();
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
		//_buildCustomParamers();
	}


	void D3d11CustomBuffer::setCustomVariable(const HString& name, const pointer data)
	{
		/*	const custom_variable* var_ptr = _findCustomVar(name);
		if (var_ptr)
		{
		switch(var_ptr->info->type)
		{
		case SP_MATRIX44:
		{
		*(mVarBlock.As<Matrix4>(var_ptr->block_offset)) = *((Matrix4*)data);
		}
		break;
		case SP_FLOAT:
		case SP_INT:
		{
		XMemory::CopySizeT1(data, mVarBlock.GetPtr(var_ptr->block_offset));
		}
		break;

		case SP_FLOAT2:
		{
		XMemory::CopySizeT2(data, mVarBlock.GetPtr(var_ptr->block_offset));
		}
		break;
		case SP_FLOAT3:
		{
		XMemory::CopySizeT3(data, mVarBlock.GetPtr(var_ptr->block_offset));
		}
		break;
		case SP_FLOAT4:
		{
		XMemory::CopySizeT4(data, mVarBlock.GetPtr(var_ptr->block_offset));
		}
		break;
		default:
		break;
		}
		}*/
	}

	void D3d11CustomBuffer::_buildConstBuffer(const D3D11_SHADER_INPUT_BIND_DESC& bind, ID3D11ShaderReflection* pReflector)
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
		
		HString name = bind.Name;

		const D3d11SystemBuffer& systemBuffer = D3d11Driver::GetSingletonPtr()->GetD3d11SystemBuffer();

		if (systemBuffer.IsSystemConstBuffer(name))
		{
			shader_log("\tsystem buffer.", sbDesc.Size);
		}
		else
		{
			shader_log("\tcustom buffer.", sbDesc.Size);
			ConstBufferPtr constBuffer = _findCustomConstBuffer(name);
			if (nullptr == constBuffer)
			{
				constBuffer = mCustomConstBuffers.push_back<D3d11ConstBuffer>();
				constBuffer->Set(name, SP_UNKNOWN);
				constBuffer->Resize(sbDesc.Size, 0);
			}
			else
			{
				shh_assert(constBuffer->GetSize() == sbDesc.Size);
			}

			for (size_t j = 0; j < sbDesc.Variables; j++) 
			{ 
				ID3D11ShaderReflectionVariable* pVReflector = pCBReflector->GetVariableByIndex(j); 
				D3D11_SHADER_VARIABLE_DESC varDesc; 
				pVReflector->GetDesc(&varDesc);

				// Only parse if variable is used
				if (varDesc.uFlags & D3D_SVF_USED)
				{
					HString valueName = varDesc.Name;
					BoundResourcePtr boundResource = _findCustomVariable(valueName);
					if (nullptr == boundResource)
					{						
						D3d11BoundValue* boundValue = mCustomVariables.push_back<D3d11BoundValue>();
						D3D11_SHADER_TYPE_DESC varTypeDesc;
						ID3D11ShaderReflectionType* varType = pVReflector->GetType();
						varType->GetDesc(&varTypeDesc);
						EShaderParam type = _get_param_type(varTypeDesc);
						boundValue->SetInfo(valueName, type, constBuffer, varDesc.StartOffset, varDesc.Size);
					}	
					shader_log("\t\t\tName:%s, StartOffset: %d, Size: %d", varDesc.Name, varDesc.StartOffset, varDesc.Size); 
				}
			}
		}

	}


	D3d11CustomBuffer::BoundResourcePtr D3d11CustomBuffer::_findCustomVariable(const HString& name) const
	{
		CustomVariables::const_iterator it = mCustomVariables.begin();
		CustomVariables::const_iterator end = mCustomVariables.end();
		while(it != end)
		{
			if ((*it)->GetName().equal(name))
			{
				return (*it);
			}
			++it;
		}
		return nullptr;
	}

	D3d11CustomBuffer::ConstBufferPtr D3d11CustomBuffer::_findCustomConstBuffer(const HString& name) const
	{
		ConstBuffers::const_iterator it = mCustomConstBuffers.begin();
		ConstBuffers::const_iterator end = mCustomConstBuffers.end();
		while(it != end)
		{
			if ((*it)->GetName().equal(name))
			{
				return (*it);
			}
			++it;
		}
		return nullptr;
	}
}