#include "D3d11_Utility.h"
namespace Shh
{
	class SematicMap
	{
	public:
		SematicMap();
		const U8String& operator [] (const ShaderSematic& sematic) const;
		U8String mStr[ShaderSematic::COUNT];
		U8String mEmpty;
	protected:

	private:
		SematicMap(const SematicMap&){};
	};

	SematicMap::SematicMap()
	{
		mStr[ShaderSematic::POSITION] = "POSITION";
		mStr[ShaderSematic::BLENDWEIGHT] = "BLENDWEIGHT";
		mStr[ShaderSematic::BLENDINDICES] = "BLENDINDICES";
		mStr[ShaderSematic::NORMAL] = "NORMAL";
		mStr[ShaderSematic::PSIZE] = "PSIZE";
		mStr[ShaderSematic::TEXCOORD] = "TEXCOORD";
		mStr[ShaderSematic::TANGENT] = "TANGENT";
		mStr[ShaderSematic::BINORMAL] = "";
		mStr[ShaderSematic::TESSFACTOR] = "TESSFACTOR";
		mStr[ShaderSematic::POSITIONT] = "POSITIONT";
		mStr[ShaderSematic::COLOR] = "COLOR";
		mStr[ShaderSematic::FOG] = "FOG";
		mStr[ShaderSematic::DEPTH] = "DEPTH";
		mStr[ShaderSematic::SAMPLE] = "";
	}

	const U8String& SematicMap::operator [] (const ShaderSematic& sematic) const
	{
		if (0 <= sematic.toValue() && sematic.toValue() < (size_t)ShaderSematic::COUNT)
		{
			return mStr[sematic.toValue()];
		}
		return mEmpty;
	}

	static const SematicMap gSematicMap;

	namespace d3d11convert
	{
		DXGI_FORMAT to(const InputElementFormat& value)
		{
			switch (value.getEnum())
			{
			case InputElementFormat::Float:     return DXGI_FORMAT_R32_FLOAT;
			case InputElementFormat::Float2:    return DXGI_FORMAT_R32G32_FLOAT;
			case InputElementFormat::Float3:    return DXGI_FORMAT_R32G32B32_FLOAT;
			case InputElementFormat::Float4:    return DXGI_FORMAT_R32G32B32A32_FLOAT;
			case InputElementFormat::UByte4:    return DXGI_FORMAT_R8G8B8A8_UINT ;
			case InputElementFormat::Short2:    return DXGI_FORMAT_R16G16_FLOAT;
			case InputElementFormat::Short4:    return DXGI_FORMAT_R16G16B16A16_FLOAT;
			case InputElementFormat::ColorBGRA: return DXGI_FORMAT_B8G8R8A8_TYPELESS;
			case InputElementFormat::ColorRGBA: return DXGI_FORMAT_R8G8B8A8_UINT;

			default:
				break;
			}
			return DXGI_FORMAT_UNKNOWN;
		}

		DXGI_FORMAT to(const IndexBufferFormat& value)
		{
			switch(value.getEnum())
			{
			case IndexBufferFormat::Index16:
				{
					return DXGI_FORMAT_R16_UINT;
				}
			case IndexBufferFormat::Index32:
				{
					return DXGI_FORMAT_R32_UINT;
				}
			default:
				{
					return DXGI_FORMAT_R32_UINT;
				}
			}
		}

		const U8String& to(const ShaderSematic& value)
		{
			return gSematicMap[value];
		}
	}
}