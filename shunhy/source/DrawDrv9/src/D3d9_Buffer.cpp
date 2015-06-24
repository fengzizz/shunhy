
#include "D3d9_Buffer.h"
#if __Renderer_d3d9__
namespace Shh
{
	D3d9Buffer::D3d9Buffer(SourceUsage usage)
		: mBufferUsage(usage)
	{
	}
	D3d9Buffer::~D3d9Buffer()
	{
		//Release();
	}
	void D3d9Buffer::Release()
	{
	}
	//IRenderDriver* D3d9Buffer::GetD3d9Driver() const 
	//{
	//	return (IRenderDriver*) GetD3d9Driver();
	//}
}
#endif
