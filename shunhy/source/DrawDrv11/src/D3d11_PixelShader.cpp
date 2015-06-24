#include "D3d11_PixelShader.h"
#if __Renderer_d3d11__
namespace Shh
{
	D3d11PixelShader::D3d11PixelShader(ID3D11PixelShader* shader, ID3D11ClassLinkage* class_linkage)
		: D3d11Shader(class_linkage)
		, mPixelShader(shader)
	{
	}
	D3d11PixelShader::~D3d11PixelShader()
	{
		_release();
	}
	void D3d11PixelShader::Release()
	{
		_release();
	}
}
#endif
