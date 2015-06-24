#ifndef __INPUT_LAYOUT_H__
#define __INPUT_LAYOUT_H__

#include "DrawDrv/RenderFormat.h"
#include "DrawDrv/InputElement.h"
#include "DrawDrv/RenderResource.h"
//
// 
//
namespace Shh
{

	class _Shh_Export InputLayout : public RenderResource
	{
		public:
			typedef std::vector<InputElement> InputElements;

			virtual ~InputLayout();

			const InputLayout::InputElements& GetElements();

			size_t GetStrides() const;

	protected:		
		InputLayout(const InputElements& elems);
	private:
		InputElements mInputElements;
		size_t mVertexStrides;
	};

	inline size_t InputLayout::GetStrides() const
	{
		return mVertexStrides;
	}
}

#endif