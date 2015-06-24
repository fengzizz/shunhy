#include "RenderData.h"
#include "InputLayout.h"

namespace Shh
{
	InputLayout::InputLayout(const InputElements& elems)
		:mInputElements(elems)
	{
		mVertexStrides = CalculateVertexStrides(mInputElements);
	}

	InputLayout::~InputLayout()
	{

	}

	const InputLayout::InputElements& InputLayout::GetElements()
	{
		return mInputElements;
	}
}