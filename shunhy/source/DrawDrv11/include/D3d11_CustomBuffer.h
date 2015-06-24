#ifndef __D3D11_CUSTOMBUFFER_H__
#define __D3D11_CUSTOMBUFFER_H__
#include "Core/HString.h"
#include "D3d11_Common.h"
#include "PtrArray.h"
namespace Shh
{

	class D3d11CustomBuffer
	{
	public:
		D3d11CustomBuffer();
		virtual ~D3d11CustomBuffer();
		virtual void Release();
		//virtual void SetCustomVariable(const HString& name, const void* data) = 0;
		void BuildParamers(ID3D11ShaderReflection* pReflector);

	protected:
		void setCustomVariable(const HString& name, const pointer data);
	private:
		typedef D3d11ConstBuffer* ConstBufferPtr;
		typedef D3d11BoundResource* BoundResourcePtr;
		typedef ptrarray<D3d11ConstBuffer> ConstBuffers;
		typedef ptrarray<D3d11BoundResource> CustomVariables;

		void _release();
		void _buildConstBuffer(const D3D11_SHADER_INPUT_BIND_DESC& bind, ID3D11ShaderReflection* pReflector);
		BoundResourcePtr _findCustomVariable(const HString& name) const;
		ConstBufferPtr _findCustomConstBuffer(const HString& name) const;

		ConstBuffers mCustomConstBuffers;
		CustomVariables mCustomVariables;
	};
}

#endif //__D3D11_CUSTOMBUFFER_H__