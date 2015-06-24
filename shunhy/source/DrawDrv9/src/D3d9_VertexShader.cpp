#include "D3d9_VertexShader.h"
#if __Renderer_d3d9__
namespace Shh
{
	D3d9VertexShader::D3d9VertexShader(IDirect3DVertexShader9* shader)
		: mVertexShader(shader)
	{

	}
	D3d9VertexShader::~D3d9VertexShader()
	{
		_release();
	}
	void D3d9VertexShader::Release()
	{
		_release();
	}

}
#endif
