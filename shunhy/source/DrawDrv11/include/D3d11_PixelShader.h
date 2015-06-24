#pragma once
#include "D3d11_Shader.h"
namespace Shh
{
	class D3d11PixelShader : public D3d11Shader
	{
	public:
		D3d11PixelShader(ID3D11PixelShader* shader, ID3D11ClassLinkage* class_linkage);
		virtual ~D3d11PixelShader();
		virtual void Release() override;
		ID3D11PixelShader* GetShader() const;
	protected:
		ID3D11PixelShader* mPixelShader;
	private:
		void _release();
	};
	inline void D3d11PixelShader::_release()
	{
		D3d11Common::DeleteCOMptr(mPixelShader);
	}

	inline ID3D11PixelShader* D3d11PixelShader::GetShader() const
	{
		return mPixelShader;
	}
}