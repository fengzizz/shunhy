#pragma once
#include "MathCoreDef.h"
#include "VectorDef.h"
#include "MatrixDef.h"
#include "MathCore.h"
namespace Shh
{
	inline Vector4 Vector4::operator +(const Vector4& vec4) const
	{
		return Vector4(x + vec4.x, y + vec4.y, z + vec4.z, w + vec4.w);
	}
	inline Vector4 Vector4::operator -(const Vector4& vec4) const
	{
		return Vector4(x - vec4.x, y - vec4.y, z - vec4.z, w - vec4.w);
	}
	inline Vector4 Vector4::operator *(const Vector4& vec4) const
	{
		return Vector4(x * vec4.x, y * vec4.y, z * vec4.z, w * vec4.w);
	}
	inline Vector4 Vector4::operator *(Single scale)
	{
		return Vector4(x * scale, y * scale, z * scale, w * scale);
	}
	inline Vector4 operator *(Single scale, const Vector4& vec4)
	{
		return Vector4(vec4.x * scale, vec4.y * scale, vec4.z * scale, vec4.w * scale);
	}
	inline Vector4 Vector4::operator /(const Vector4& vec4) const
	{
		shh_assert(0 != vec4.x);
		shh_assert(0 != vec4.y);
		shh_assert(0 != vec4.z);
		shh_assert(0 != vec4.w);

		return Vector4(x / vec4.x, y / vec4.y, z / vec4.z, w / vec4.w);
	}
	inline Vector4 Vector4::operator /(Single scale) const
	{
		shh_assert(0 != scale);
		return Vector4(x / scale, y / scale, z / scale, w / scale);
	}
	inline Vector4& Vector4::operator +=(const Vector4& vec4)
	{
		x += vec4.x;
		y += vec4.y;
		z += vec4.z;
		w += vec4.w;
		return *this;
	}
	inline Vector4& Vector4::operator -=(const Vector4& vec4)
	{
		x -= vec4.x;
		y -= vec4.y;
		z -= vec4.z;
		w -= vec4.w;
		return *this;
	}
	inline Vector4& Vector4::operator *=(const Vector4& vec4)
	{
		x *= vec4.x;
		y *= vec4.y;
		z *= vec4.z;
		w *= vec4.w;
		return *this;
	}
	inline Vector4& Vector4::operator *=(Single vec4)
	{
		x *= vec4;
		y *= vec4;
		z *= vec4;
		w *= vec4;
		return *this;
	}
	inline Vector4& Vector4::operator /=(const Vector4& vec4)
	{
		shh_assert(0 != vec4.x);
		shh_assert(0 != vec4.y);
		shh_assert(0 != vec4.z);
		shh_assert(0 != vec4.w);
		x /= vec4.x;
		y /= vec4.y;
		z /= vec4.z;
		w /= vec4.w;
		return *this;
	}
	inline Vector4& Vector4::operator /=(Single vec4)
	{
		shh_assert(0 != vec4);
		x /= vec4;
		y /= vec4;
		z /= vec4;
		w /= vec4;
		return *this;

	}
	inline Vector4 Vector4::operator -() const
	{
		return Vector4(-x, -y, -z, -w);
	}
	inline bool Vector4::operator ==(const Vector4& vec4) const
	{
		return (x == vec4.x) && (y == vec4.y) && (z == vec4.z) && (w == vec4.w);
	}
	inline bool Vector4::operator !=(const Vector4& vec4) const
	{
		return (x != vec4.x) && (y != vec4.y) && (z != vec4.z) && (w != vec4.w);
	}
	inline Vector4 Vector4::operator * (const Matrix4& mat4)  const
	{
		return Vector4(
			x * mat4[0][0] + y * mat4[1][0] + z * mat4[2][0] + w * mat4[3][0],
			x * mat4[0][1] + y * mat4[1][1] + z * mat4[2][1] + w * mat4[3][1],
			x * mat4[0][2] + y * mat4[1][2] + z * mat4[2][2] + w * mat4[3][2],
			x * mat4[0][3] + y * mat4[1][3] + z * mat4[2][3] + w * mat4[3][3]);
	}
	inline Vector4 Vector4::operator * (const Matrix43& mat43)  const
	{
		return Vector4(
			x * mat43[0][0] + y * mat43[1][0] + z * mat43[2][0] + w * mat43[3][0],
			x * mat43[0][1] + y * mat43[1][1] + z * mat43[2][1] + w * mat43[3][1],
			x * mat43[0][2] + y * mat43[1][2] + z * mat43[2][2] + w * mat43[3][2],
			w);
	}
	inline Vector4 Vector4::operator * (const Matrix3& mat3)  const
	{
		return Vector4(
			x * mat3[0][0] + y * mat3[1][0] + z * mat3[2][0],
			x * mat3[0][1] + y * mat3[1][1] + z * mat3[2][1],
			x * mat3[0][2] + y * mat3[1][2] + z * mat3[2][2],
			w);
	}

	inline void Vector4::Transform(const Matrix4& mat4)
	{
		x = x * mat4[0][0] + y * mat4[1][0] + z * mat4[2][0] + w * mat4[3][0];
		y = x * mat4[0][1] + y * mat4[1][1] + z * mat4[2][1] + w * mat4[3][1];
		z = x * mat4[0][2] + y * mat4[1][2] + z * mat4[2][2] + w * mat4[3][2];
		w = x * mat4[0][3] + y * mat4[1][3] + z * mat4[2][3] + w * mat4[3][3];
	}
	inline void Vector4::Transform(const Matrix43& mat43)
	{
		x = x * mat43[0][0] + y * mat43[1][0] + z * mat43[2][0] + w * mat43[3][0];
		y = x * mat43[0][1] + y * mat43[1][1] + z * mat43[2][1] + w * mat43[3][1];
		z = x * mat43[0][2] + y * mat43[1][2] + z * mat43[2][2] + w * mat43[3][2];
	}
	inline void Vector4::Transform(const Matrix3& mat3)
	{
		x = x * mat3[0][0] + y * mat3[1][0] + z * mat3[2][0];
		y = x * mat3[0][1] + y * mat3[1][1] + z * mat3[2][1];
		z = x * mat3[0][2] + y * mat3[1][2] + z * mat3[2][2];
	}
	inline Single Vector4::SquaredLength() const
	{
		return (x * x + y * y) + (z * z + w * w);
	}
	inline Single Vector4::Length() const
	{
		return Math::Sqrt(SquaredLength());
	}
	inline void Vector4::Normalize()
	{
		Single num2 = SquaredLength();
		shh_assert(num2 != 0.0f);
		Single num = 1.0f / ((Single) Math::Sqrt(num2));
		x *= num;
		y *= num;
		z *= num;
		w *= num;

	}

	inline Single Vector4::DistanceSquared(const Vector4& value1, const Vector4& value2)
	{
		float num4 = value1.x - value2.x;
		float num3 = value1.y - value2.y;
		float num2 = value1.z - value2.z;
		float num = value1.w - value2.w;
		return (num4 * num4 + num3 * num3) + (num2 * num2 + num * num);

	}
	inline Single Vector4::Distance(const Vector4& value1, const Vector4& value2)
	{
		return Math::Sqrt(DistanceSquared(value1, value2));
	}
	inline Single Vector4::Dot(const Vector4& value1, const Vector4& value2)
	{
		return (value1.x * value2.x + value1.y * value2.y) + (value1.z * value2.z + value1.w * value2.w);
	}
}