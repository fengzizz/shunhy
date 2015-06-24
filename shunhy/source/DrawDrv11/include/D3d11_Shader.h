#ifndef __D3D11_SHADER_H__
#define __D3D11_SHADER_H__
#include <vector>
#include <d3d11shader.h>
#include "Core/Memory.h"
#include "D3d11_InputBinding.h"
#include "D3d11_Common.h"

namespace Shh
{

	class D3d11ShaderReflection
	{
	public:
		void Build(ID3D11ShaderReflection* pReflector);
	private:
		void _buildCBuffer(const D3D11_SHADER_INPUT_BIND_DESC& bind, ID3D11ShaderReflection* pReflector);
		void _buildCTexture(const D3D11_SHADER_INPUT_BIND_DESC& bind, ID3D11ShaderReflection* pReflector);
		void _buildCSampler(const D3D11_SHADER_INPUT_BIND_DESC& bind, ID3D11ShaderReflection* pReflector);

		CBufferBindings mCBufferBindings;
		VariableBindings mVariableBindings;
		TextureBindings mTextureBindings;
		SamplerBindings	mSamplerBindings;
	};


	class D3d11Shader
	{
	public:
		D3d11Shader(ID3D11ClassLinkage* class_linkage);
		virtual ~D3d11Shader();
		virtual void Release();
		void Bind(ID3D11ShaderReflection* pReflector);
	private:
		void _release();
		D3d11ShaderReflection mReflection;
		ID3D11ClassLinkage* mClassLinkage;
	};

}
#endif //__D3D11_SHADER_H__

