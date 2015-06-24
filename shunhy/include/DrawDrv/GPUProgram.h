#ifndef __GPUPROGRAM_H__
#define __GPUPROGRAM_H__

#include "Core/HString.h"
#include "DrawDrv/RenderFormat.h"
#include "DrawDrv/RenderResource.h"

namespace Shh
{

	enum EShaderParam
	{
		SP_UNKNOWN = -1,
		SP_MATRIX44,
		SP_FLOAT4,
		SP_FLOAT3,
		SP_FLOAT2,
		SP_FLOAT,
		SP_INT,
		SP_TEXTURE,
	};

	class _Shh_Export GPUProgram : public RenderResource
	{
	public:
		GPUProgram(const U8String& name);
		virtual ~GPUProgram() {}
	private:
		U8String mName;
	};

	inline GPUProgram::GPUProgram(const U8String& name)
		:mName(name)
	{

	}
}

#endif // __GPUPROGRAM_H__
