#ifndef __D3D11_GPUPROGRAME_H__
#define __D3D11_GPUPROGRAME_H__

#include "Core/HString.h"
#include "DrawDrv/GPUProgram.h"
#include "D3d11_Common.h"

//
// 
//

namespace Shh
{
	class D3d11GPUProgram : public GPUProgram, public D3d11Resource
	{
	public:
		virtual bool Valid() const;
		D3d11GPUProgram(const U8String& name, D3d11VertexShader* vs, D3d11PixelShader* ps);
		virtual ~D3d11GPUProgram();
		virtual void Release() override;
		D3d11VertexShader* GetVertexShader() const;
		D3d11PixelShader* GetPixelShader() const;

	protected:
		ID3D11ClassLinkage* mClassLinkage;
	private:
		void _release();
		D3d11VertexShader* mVertexShader;
		D3d11PixelShader* mPixelShader;
	};

	inline D3d11VertexShader* D3d11GPUProgram::GetVertexShader() const
	{
		return mVertexShader;
	}
	inline D3d11PixelShader* D3d11GPUProgram::GetPixelShader() const
	{
		return mPixelShader;
	}
}

#endif
