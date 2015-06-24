#include "D3d11_Utility.h"
#include "D3d11_InputLayout.h"
#if __Renderer_d3d11__
// 
//

namespace Shh
{

	D3d11InputLayout::D3d11InputLayout(const InputLayout::InputElements& elems, ID3D11InputLayout* layout, D3d11Driver* driver)
		:super(elems) 
		,mLayout(layout)
	{

	}
	D3d11InputLayout::~D3d11InputLayout()
	{
		Release();
	}

	bool D3d11InputLayout::Valid() const
	{
		return NULL != mLayout;
	}
	void D3d11InputLayout::Release()
	{
		D3d11Common::DeleteCOMptr(mLayout);
	}
	void D3d11InputLayout::TransInputElement(const InputElement& src, D3D11_INPUT_ELEMENT_DESC& dest)
	{
		dest.SemanticName = d3d11convert::to(src.GetSematic()).c_str();
		dest.SemanticIndex = src.GetSemanticIndex();
		dest.Format = d3d11convert::to(src.GetFormat());
		dest.InputSlot = src.GetInputSlot();

		dest.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		dest.InstanceDataStepRate = 0;
		dest.AlignedByteOffset = 0;
	}
}

#endif
