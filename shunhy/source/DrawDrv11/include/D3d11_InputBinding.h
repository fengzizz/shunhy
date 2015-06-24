#ifndef __D3D11_INPUTBINDING_H__
#define __D3D11_INPUTBINDING_H__
#include "Core/U8String.h"
namespace Shh
{

	class CBufferBinding
	{
	public:
		U8String Name;
		int BindPoint;
		int BindCount;
		int Variables;
		int Size;
		CBufferBinding()
			:BindPoint(0)
			,BindCount(0)
			,Variables(0)
			,Size(0)
		{
		}
	};

	class VariableBinding
	{
	public:
		U8String Name;
		int BufferIndex;
		int StartOffset;
		int Size;

		VariableBinding()
			:BufferIndex(0)
			,StartOffset(0)
			,Size(0)
		{

		}
	};
	class SamplerBinding
	{
	public:
		U8String Name;
		int BindPoint;
		int BindCount;

		SamplerBinding()
			:BindPoint(0)
			,BindCount(0)
		{
		}
	};

	class TextureBinding
	{
	public:

		U8String Name;
		int BindPoint;
		int BindCount;

		TextureBinding()
			:BindPoint(0)
			,BindCount(0)

		{
		}
	};


	typedef std::vector<CBufferBinding> CBufferBindings;
	typedef std::vector<VariableBinding> VariableBindings;
	typedef std::vector<TextureBinding> TextureBindings;
	typedef std::vector<SamplerBinding> SamplerBindings;


}

#endif //__D3D11_INPUTBINDING_H__