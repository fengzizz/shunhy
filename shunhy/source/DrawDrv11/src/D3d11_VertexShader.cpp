#include "D3d11_VertexShader.h"
#if __Renderer_d3d11__
namespace Shh
{
	D3d11VertexShader::D3d11VertexShader(ID3D11VertexShader* shader, ID3D11ClassLinkage* class_linkage)
		: D3d11Shader(class_linkage)
		, mVertexShader(shader)
	{

	}
	D3d11VertexShader::~D3d11VertexShader()
	{
		_release();
	}
	void D3d11VertexShader::Release()
	{
		_release();
	}

	//void D3d11VertexShader::SetCustomVariable(const HString& name, const pointer data)
	//{
	//	setCustomVariable(name, data);
	//}
}
#endif
