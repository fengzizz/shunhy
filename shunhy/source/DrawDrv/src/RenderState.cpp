#include "RenderState.h"
#include "Core/StringUtility.h"
namespace Shh
{


	__Implement_Enum(CullMode);
	__Regist_Enum_Suite(CullMode, None);
	__Regist_Enum_Suite(CullMode, Front);
	__Regist_Enum_Suite(CullMode, Back);

	__Implement_Enum(FillMode);
	__Regist_Enum_Suite(FillMode, Point);
	__Regist_Enum_Suite(FillMode, Wireframe);
	__Regist_Enum_Suite(FillMode, Solid);

	__Implement_Enum(BlendOperation);
	__Regist_Enum_Suite(BlendOperation, Add);
	__Regist_Enum_Suite2(BlendOperation, Subtract, Sub);
	__Regist_Enum_Suite2(BlendOperation, RevSubtract, RevSub);
	__Regist_Enum_Suite(BlendOperation, Min);
	__Regist_Enum_Suite(BlendOperation, Max);

	__Implement_Enum(BlendFactor);
	__Regist_Enum_Suite(BlendFactor, Zero);
	__Regist_Enum_Suite(BlendFactor, One);
	__Regist_Enum_Suite(BlendFactor, SrcColor);
	__Regist_Enum_Suite(BlendFactor, InvSrcColor);
	__Regist_Enum_Suite(BlendFactor, SrcAlpha);
	__Regist_Enum_Suite(BlendFactor, InvSrcAlpha);
	__Regist_Enum_Suite(BlendFactor, DestAlpha);
	__Regist_Enum_Suite(BlendFactor, InvDestAlpha);
	__Regist_Enum_Suite(BlendFactor, DestColor);
	__Regist_Enum_Suite(BlendFactor, InvDestColor);
	__Regist_Enum_Suite(BlendFactor, SrcAlphaSat);

	__Regist_Enum_Suite(BlendFactor, BlentFactor);
	__Regist_Enum_Suite(BlendFactor, InvBlentFactor);
	__Regist_Enum_Suite(BlendFactor, Src1Color);
	__Regist_Enum_Suite(BlendFactor, InvSrc1Color);
	__Regist_Enum_Suite(BlendFactor, Src1Alpha);
	__Regist_Enum_Suite(BlendFactor, InvSrc1Alpha);



	__Implement_Enum(ComparisonFunction);
	__Regist_Enum_Suite(ComparisonFunction, Nerver);
	__Regist_Enum_Suite(ComparisonFunction, Less);
	__Regist_Enum_Suite(ComparisonFunction, Equal);
	__Regist_Enum_Suite(ComparisonFunction, LessEqual);
	__Regist_Enum_Suite(ComparisonFunction, Grater);
	__Regist_Enum_Suite(ComparisonFunction, NotEqual);
	__Regist_Enum_Suite(ComparisonFunction, GraterEqual);
	__Regist_Enum_Suite(ComparisonFunction, Always);


	__Implement_Enum(StencilOperation);
	__Regist_Enum_Suite(StencilOperation, Keep);
	__Regist_Enum_Suite(StencilOperation, Zero);
	__Regist_Enum_Suite(StencilOperation, Replace);
	__Regist_Enum_Suite(StencilOperation, IncrSat);
	__Regist_Enum_Suite(StencilOperation, DecrSat);
	__Regist_Enum_Suite(StencilOperation, Invert);
	__Regist_Enum_Suite(StencilOperation, Incr);
	__Regist_Enum_Suite(StencilOperation, Decr);

	__Implement_Enum(TextureAddressMode);
	__Regist_Enum_Suite(TextureAddressMode, Wrap);
	__Regist_Enum_Suite(TextureAddressMode, Mirror);
	__Regist_Enum_Suite(TextureAddressMode, Clamp);
	__Regist_Enum_Suite(TextureAddressMode, Border);
	__Regist_Enum_Suite(TextureAddressMode, MirrorOnce);

	__Implement_Enum(TextureFilter);
	__Regist_Enum_Suite(TextureFilter, Point);
	__Regist_Enum_Suite(TextureFilter, Linear);
	__Regist_Enum_Suite(TextureFilter, Anisotropic);

	template<typename _T>
	inline bool _parse(const U8String& _name, _T& _value)
	{
		int result;
		if(_T::_GetConvertMap().parseString(_name, result))
		{
			_value = (_T::Enum)result;
			return true;
		}
		return false;
	}

	bool CullMode::parse(const U8String& name, CullMode& mode)
	{
		return _parse(name, mode);
	}

	bool FillMode::parse(const U8String& name, FillMode& mode)
	{
		return _parse(name, mode);
	}

	bool BlendOperation::parse(const U8String& name, BlendOperation& operation)
	{
		return _parse(name, operation);
	}

	bool BlendFactor::parse(const U8String& name, BlendFactor& factor)
	{
		return _parse(name, factor);
	}

	bool ComparisonFunction::parse(const U8String& name, ComparisonFunction& func)
	{
		return _parse(name, func);
	}

	bool StencilOperation::parse(const U8String& name, StencilOperation& op)
	{
		return _parse(name, op);
	}

	bool TextureAddressMode::parse(const U8String& name, TextureAddressMode& mode)
	{
		return _parse(name, mode);
	}

	bool TextureFilter::parse(const U8String& name, TextureFilter& filter)
	{
		return _parse(name, filter);
	}

	bool ColorWriteMask::parse(const U8String& name, ColorWriteMask& mark)
	{
		if (name.empty())
		{
			mark = ColorWriteMask::None;
			return true;
		}
		uint temp = (uint)ColorWriteMask::None;
		for (size_t i = 0; i < name.length(); ++i)
		{
			char c = name[i];
			switch(c)
			{
			case 'R':
			case 'r':
				{
					temp |= ColorWriteMask::Red;
					break;
				}
			case 'G':
			case 'g':
				{
					temp |= ColorWriteMask::Green;
					break;
				}
			case 'B':
			case 'b':
				{
					temp |= ColorWriteMask::Blue;
					break;
				}
			case 'A':
			case 'a':
				{
					temp |= ColorWriteMask::Alpha;
					break;
				}
			default:
				{
					return false;
				}
			}
		}
		mark = (ColorWriteMask::Enum)temp;
		return true;
	}

	DeviceRasterizerState::DeviceRasterizerState()
		: fillMode(FillMode::Solid),
		cullMode(CullMode::Back),
		slopScaleDepthBias(0),
		depthBias(0),
		scissorTestEnable(false),
		multisampleEnable(true)
	{
	}

	DeviceDepthAndStencilState::DeviceDepthAndStencilState()
		: depthTestEnable(true),
		depthWriteEnable(true),
		depthFunc(ComparisonFunction::LessEqual),
		stencilRef(0),
		stencilEnable(false),
		stencilFunc(ComparisonFunction::Always),
		stencilReadMask(0xFF),
		stencilWriteMask(0xFF),
		stencilFail(StencilOperation::Keep),
		stencilZFail(StencilOperation::Keep),
		stencilPass(StencilOperation::Keep),
		stencilBackCustom(false),
		stencilBackFunc(ComparisonFunction::Always),
		stencilBackFail(StencilOperation::Keep),
		stencilBackZFail(StencilOperation::Keep),
		stencilBackPass(StencilOperation::Keep)

	{
	}

	DeviceTargetBlendState::DeviceTargetBlendState()
		:alphaBlendEnable(false),
		blendOP(BlendOperation::Add),
		srcBlend(BlendFactor::Zero),
		destBlend(BlendFactor::One),
		blendOPAlpha(BlendOperation::Add),
		srcBlendAlpha(BlendFactor::Zero),
		destBlendAlpha(BlendFactor::One),
		colorWriteMask(ColorWriteMask::All)
	{

	}

	DeviceBlendState::DeviceBlendState()
		: alphaTestEnable(false),
		alphaFunc(ComparisonFunction::Always),
		alphaRef(0),
		separateAlphaBlendEnable(false)
	{
	}

	SamplerState::SamplerState()
	{
		textureIndexEnable = false;
		addressU = TextureAddressMode::Wrap;
		addressV = TextureAddressMode::Wrap;
		addressW = TextureAddressMode::Wrap;
		Filter = TextureFilter::Point;
		maxAnisotropy = 1;
		textureType = RT_TEX2D;
	}

}
