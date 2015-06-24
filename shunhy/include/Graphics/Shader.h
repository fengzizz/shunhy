#ifndef __SHADER_H__
#define __SHADER_H__

#include "Core/Nameable.h"
#include "Core/PtrArray.h"
#include "DrawDrv/ShaderParameter.h"
#include "DrawDrv/RenderStateDesc.h"
#include "Graphics/RenderHandle.h"
#include "Resource/Resource.h"

namespace Shh
{

	class _Shh_Export ShaderPass : public Nameable
	{
	public:
		ShaderPass();

		inline void _SetGPUProgramHandle(RenderHandle program)
		{
			mProgram = program;
		}

		inline RenderStateDesc& _GetDesc()
		{
			return mRenderStateDesc;
		}

		inline ShaderParameters& _GetParameters()
		{
			return mParameters;
		}

	private:
		RenderStateDesc mRenderStateDesc;
		ShaderParameters mParameters;
		RenderHandle mProgram;
	};

	class _Shh_Export Technique : public Nameable
	{
	public:

		void _AddPass(ShaderPass* pass);
	private:
		typedef ptrarray<ShaderPass> Passes;
		Passes mPasses;
	};


	class _Shh_Export Shader : public Resource
	{
	public:

		void _AddTech(Technique* tech);
	private:
		typedef ptrarray<Technique> Techniques;

		Techniques mTechniques;
	};
}
#endif //__SHADER_H__

