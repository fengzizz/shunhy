#pragma once
#include "MathCoreDef.h"
#include "VectorDef.h"
#include "MathCore.h"
namespace Shh
{
	inline Vector2 Vector2::operator +(const Vector2& vec2) const
	{
		return Vector2(x + vec2.x, y + vec2.y);
	}
	inline Vector2 Vector2::operator -(const Vector2& vec2) const
	{
		return Vector2(x - vec2.x, y - vec2.y);
	}
	inline Vector2 Vector2::operator *(const Vector2& vec2) const
	{
		return Vector2(x * vec2.x, y * vec2.y);
	}
	inline Vector2 Vector2::operator *(Single scale) const
	{
		return Vector2(x * scale, y * scale);
	}
	inline Vector2 operator *(Single scale, const Vector2& vec2)
	{
		return Vector2(vec2.x * scale, vec2.y * scale);
	}
	inline Vector2 Vector2::operator /(Single scale) const
	{
		shh_assert(0 != scale);
		return Vector2(x / scale, y / scale);
	}
	inline Vector2 Vector2::operator /(const Vector2& vec2) const
	{
		shh_assert(0 != x);
		shh_assert(0 != y);
		return Vector2(x / vec2.x, y / vec2.y);
	}
	inline Vector2& Vector2::operator +=(const Vector2& vec2)
	{
		x += vec2.x;
		y += vec2.y;
		return *this;
	}
	inline Vector2& Vector2::operator -=(const Vector2& vec2)
	{
		x -= vec2.x;
		y -= vec2.y;
		return *this;
	}
	inline Vector2& Vector2::operator *=(const Vector2& vec2)
	{
		x *= vec2.x;
		y *= vec2.y;
		return *this;
	}
	inline Vector2& Vector2::operator *=(Single vec2)
	{
		x *= vec2;
		y *= vec2;
		return *this;
	}
	inline Vector2& Vector2::operator /=(const Vector2& vec2)
	{
		shh_assert(0 != vec2.x);
		shh_assert(0 != vec2.y);
		x /= vec2.x;
		y /= vec2.y;
		return *this;
	}
	inline Vector2& Vector2::operator /=(Single vec2)
	{
		shh_assert(0 != vec2);
		x /= vec2;
		y /= vec2;
		return *this;

	}
	inline Vector2 Vector2::operator -() const
	{
		return Vector2(-x, -y);
	}
	inline bool Vector2::operator ==(const Vector2& vec2) const
	{
		return (x == vec2.x) && (y == vec2.y);
	}
	inline bool Vector2::operator !=(const Vector2& vec2) const
	{
		return (x != vec2.x) && (y != vec2.y);
	}
	inline Single Vector2::SquaredLength() const
	{
		return x * x + y * y;
	}
	inline Single Vector2::Length() const
	{
		return Math::Sqrt(SquaredLength());
	}
	inline void Vector2::Normalize()
	{
		Single num2 = SquaredLength();
		shh_assert(num2 != 0.0f);
		Single num = 1.0f / ((Single) Math::Sqrt(num2));
		x *= num;
		y *= num;
	}

	inline Single Vector2::DistanceSquared(const Vector2& value1, const Vector2& value2)
	{
		float num2 = value1.x - value2.x;
		float num = value1.y - value2.y;
		return ((num2 * num2) + (num * num));
	}
	inline Single Vector2::Distance(const Vector2& value1, const Vector2& value2)
	{
		return Math::Sqrt(DistanceSquared(value1, value2));
	}
	inline Single Vector2::Dot(const Vector2& value1, const Vector2& value2)
	{
		return ((value1.x * value2.x) + (value1.y * value2.y));

	}

}