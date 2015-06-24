#include "D3d11_Buffer.h"
#if __Renderer_d3d11__
namespace Shh
{
	D3d11Buffer::D3d11Buffer(ID3D11Buffer* buffer)
		: mBuffer(buffer)
	{
	}
	D3d11Buffer::~D3d11Buffer()
	{
		Release();
	}
	void D3d11Buffer::Release()
	{
		D3d11Common::DeleteCOMptr(mBuffer);
	}
}
#endif
