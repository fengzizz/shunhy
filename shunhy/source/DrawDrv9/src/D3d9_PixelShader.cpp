#include "D3d9_PixelShader.h"
#if __Renderer_d3d9__
namespace Shh
{
	D3d9PixelShader::D3d9PixelShader(IDirect3DPixelShader9* shader)
		: mPixelShader(shader)
	{

	}
	D3d9PixelShader::~D3d9PixelShader()
	{
		_release();
	}
	void D3d9PixelShader::Release()
	{
		_release();
	}
}
#endif
