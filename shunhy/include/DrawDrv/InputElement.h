#ifndef __INPUT_ELEMENT_H__
#define __INPUT_ELEMENT_H__

#include "DrawDrv/DrawDrvDef.h"
#include "DrawDrv/RenderFormat.h"
//
// 
//
namespace Shh
{

	class _Shh_Export InputElement
	{
	public:
		inline InputElement(ShaderSematic sematic, size_t sematic_index, 
			InputElementFormat format, size_t input_slot, size_t byte_offest);
		ShaderSematic GetSematic() const;
		size_t GetSemanticIndex() const;
		InputElementFormat GetFormat() const;
		size_t GetInputSlot() const;
		size_t GetOffsetInByte() const;
		size_t GetSize() const;
	private:
		ShaderSematic mSematic;
		InputElementFormat mFormat;

		size_t mSemanticIndex;
		size_t mInputSlot;
		size_t mOffsetInByte;
	};
	inline InputElement::InputElement(ShaderSematic sematic, size_t sematic_index, 
		InputElementFormat format, size_t input_slot, size_t byte_offest)
		: mSematic(sematic), mSemanticIndex(sematic_index), mFormat(format)
		, mInputSlot(input_slot), mOffsetInByte(byte_offest)
	{

	}
	inline ShaderSematic InputElement::GetSematic() const
	{
		return mSematic;
	}
	inline size_t InputElement::GetSemanticIndex() const
	{
		return mSemanticIndex;
	}
	inline InputElementFormat InputElement::GetFormat() const
	{
		return mFormat;
	}
	inline size_t InputElement::GetInputSlot() const
	{
		return mInputSlot;
	}
	inline size_t InputElement::GetOffsetInByte() const
	{
		return mOffsetInByte;
	}

	inline size_t InputElement::GetSize() const
	{
		return mFormat.getSize();
	}

}

#endif //__INPUT_ELEMENT_H__
