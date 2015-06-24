#pragma once
#include "MathCoreDef.h"
#include "VectorDef.h"

namespace Shh
{
	class _Shh_Export Color//
	{
	public:		
		Color();
		explicit Color(uint32 color);
		Color(byte red, byte green, byte blue, byte alpha = 255);
		byte r,g,b,a;

		Vector3 ToVector3() const;
		Vector4 ToVector4() const;
		uint32 Touint32() const;

		bool operator == (const Color& color) const;
		bool operator != (const Color& color) const;
		Color operator * (Single scale) const;

		static const Color Empty;
		static const Color White;
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
	};

	inline Color::Color()
	{

	}
	inline Color::Color(uint32 color)
	{
		this->r = color & 0xff;
		this->g = (color>>8 & 0xff);
		this->b = (color>>16 & 0xff);
		this->a = (color>>24 & 0xff);
	}
	inline Color::Color(byte red, byte green, byte blue, byte alpha)
		: r(red), g(green), b(blue), a(alpha)
	{

	}

	inline Vector3 Color::ToVector3() const
	{
		return Vector3((Single) r, (Single)g, (Single)b);
	}
	inline Vector4 Color::ToVector4() const
	{
		return Vector4((Single) r, (Single)g, (Single)b, (Single)a);
	}
	inline uint32 Color::Touint32() const
	{
		uint32 u32 = r;
		u32 |= (this->g<<8);
		u32 |= (this->b<<16);
		u32 |= (this->a<<24);
		return u32;
	}

	inline bool Color::operator == (const Color& color) const
	{
		const uint32* p_1 = (uint32*)this;
		const uint32* p_2 = (uint32*)&color;
		return (*p_1) == (*p_2);
	}
	inline bool Color::operator != (const Color& color) const
	{
		const uint32* p_1 = (uint32*)this;
		const uint32* p_2 = (uint32*)&color;
		return (*p_1) != (*p_2);
	}
}