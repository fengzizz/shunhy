#pragma once
#include "D3d9_Common.h"
namespace Shh
{
	class D3d9VertexShader
	{
	public:
		D3d9VertexShader(IDirect3DVertexShader9* shader);
		virtual ~D3d9VertexShader();
		virtual void Release();
	protected:
		IDirect3DVertexShader9* mVertexShader;
	private:
		void _release();
	};
	inline void D3d9VertexShader::_release()
	{
		D3d9Common::DeleteCOMptr(mVertexShader);
	}
}