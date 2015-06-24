#pragma once
#include "D3d9_Common.h"
namespace Shh
{
	class D3d9PixelShader
	{
	public:
		D3d9PixelShader(IDirect3DPixelShader9* shader);
		virtual ~D3d9PixelShader();
		virtual void Release();
	protected:
		IDirect3DPixelShader9* mPixelShader;
	private:
		void _release();
	};
	inline void D3d9PixelShader::_release()
	{
		D3d9Common::DeleteCOMptr(mPixelShader);
	}
}