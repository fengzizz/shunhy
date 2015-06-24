#pragma once
#include "D3d11_Shader.h"
namespace Shh
{
	class D3d11VertexShader : public D3d11Shader
	{
	public:
		D3d11VertexShader(ID3D11VertexShader* shader, ID3D11ClassLinkage* class_linkage);
		virtual ~D3d11VertexShader();
		//virtual void SetCustomVariable(const HString& name, const pointer data) override;
		virtual void Release() override;
		ID3D11VertexShader* GetShader() const;
	protected:
		ID3D11VertexShader* mVertexShader;

	private:
		void _release();
	};
	inline void D3d11VertexShader::_release()
	{
		D3d11Common::DeleteCOMptr(mVertexShader);
	}

	inline ID3D11VertexShader* D3d11VertexShader::GetShader() const
	{
		return mVertexShader;
	}
}