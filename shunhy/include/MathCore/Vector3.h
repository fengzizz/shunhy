#pragma once
#include "MathCoreDef.h"
#include "VectorDef.h"
#include "MatrixDef.h"
#include "MathCore.h"
namespace Shh
{
	inline Vector3 Vector3::operator +(const Vector3& vec3) const
	{
		return Vector3(x + vec3.x, y + vec3.y, z + vec3.z);
	}
	inline Vector3 Vector3::operator -(const Vector3& vec3) const
	{
		return Vector3(x - vec3.x, y - vec3.y, z - vec3.z);
	}
	inline Vector3 Vector3::operator *(const Vector3& vec3) const
	{
		return Vector3(x * vec3.x, y * vec3.y, z * vec3.z);
	}

	inline Vector3 Vector3::operator *(Single scale) const
	{
		return Vector3(x * scale, y * scale, z * scale);
	}
	inline Vector3 operator *(Single scale, const Vector3& vec3)
	{
		return Vector3(vec3.x * scale, vec3.y * scale, vec3.z * scale);
	}
	inline Vector3 Vector3::operator /(const Vector3& vec3) const
	{
		shh_assert(0 != vec3.x);
		shh_assert(0 != vec3.y);
		shh_assert(0 != vec3.z);
		return Vector3(x / vec3.x, y / vec3.y, z / vec3.z);
	}
	inline Vector3 Vector3::operator /(Single scale) const
	{
		shh_assert(0 != scale);
		return Vector3(x / scale, y / scale, z / scale);
	}
	inline Vector3& Vector3::operator +=(const Vector3& value)
	{
		x += value.x;
		y += value.y;
		z += value.z;
		return *this;
	}
	inline Vector3& Vector3::operator -=(const Vector3& value)
	{
		x -= value.x;
		y -= value.y;
		z -= value.z;
		return *this;
	}
	inline Vector3& Vector3::operator *=(const Vector3& value)
	{
		x *= value.x;
		y *= value.y;
		z *= value.z;
		return *this;
	}
	inline Vector3& Vector3::operator *=(Single value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
	inline Vector3& Vector3::operator /=(const Vector3& value)
	{
		shh_assert(0 != value.x);
		shh_assert(0 != value.y);
		shh_assert(0 != value.z);
		x /= value.x;
		y /= value.y;
		z /= value.z;
		return *this;
	}
	inline Vector3& Vector3::operator /=(Single value)
	{
		shh_assert(0 != value);
		x /= value;
		y /= value;
		z /= value;
		return *this;

	}
	inline Vector3 Vector3::operator -() const
	{
		return Vector3(-x, -y, -z);
	}
	inline bool Vector3::operator ==(const Vector3& vec3) const
	{
		return (x == vec3.x) && (y == vec3.y) && (z == vec3.z);
	}
	inline bool Vector3::operator !=(const Vector3& vec3) const
	{
		return (x != vec3.x) || (y != vec3.y) || (z != vec3.z);
	}

	inline Vector3 Vector3::operator *(const Matrix4& mat4) const
	{
		return Vector3(
			x * mat4[0][0] + y * mat4[1][0] + z * mat4[2][0] + mat4[3][0],
			x * mat4[0][1] + y * mat4[1][1] + z * mat4[2][1] + mat4[3][1],
			x * mat4[0][2] + y * mat4[1][2] + z * mat4[2][2] + mat4[3][2]);
	}
	inline Vector3 Vector3::operator *(const Matrix3& mat3) const
	{
		return Vector3(
			x * mat3[0][0] + y * mat3[1][0] + z * mat3[2][0],
			x * mat3[0][1] + y * mat3[1][1] + z * mat3[2][1],
			x * mat3[0][2] + y * mat3[1][2] + z * mat3[2][2]);
	}
	inline Vector3 Vector3::operator *(const Matrix43& mat43) const
	{
		return Vector3(
			x * mat43[0][0] + y * mat43[1][0] + z * mat43[2][0] + mat43[3][0],
			x * mat43[0][1] + y * mat43[1][1] + z * mat43[2][1] + mat43[3][1],
			x * mat43[0][2] + y * mat43[1][2] + z * mat43[2][2] + mat43[3][2]);
	}

	inline void Vector3::Transform(const Matrix4& mat4)
	{
		x = x * mat4[0][0] + y * mat4[1][0] + z * mat4[2][0] + mat4[3][0];
		y = x * mat4[0][1] + y * mat4[1][1] + z * mat4[2][1] + mat4[3][1];
		z = x * mat4[0][2] + y * mat4[1][2] + z * mat4[2][2] + mat4[3][2];
	}
	inline void Vector3::Transform(const Matrix3& mat3)
	{
		x = x * mat3[0][0] + y * mat3[1][0] + z * mat3[2][0];
		y = x * mat3[0][1] + y * mat3[1][1] + z * mat3[2][1];
		z = x * mat3[0][2] + y * mat3[1][2] + z * mat3[2][2];
	}
	inline void Vector3::Transform(const Matrix43& mat43)
	{
		x = x * mat43[0][0] + y * mat43[1][0] + z * mat43[2][0] + mat43[3][0];
		y = x * mat43[0][1] + y * mat43[1][1] + z * mat43[2][1] + mat43[3][1];
		z = x * mat43[0][2] + y * mat43[1][2] + z * mat43[2][2] + mat43[3][2];
	}	
	inline Single Vector3::SquaredLength() const
	{
		return x * x + y * y + z * z;
	}
	inline Single Vector3::Length() const
	{
		return Math::Sqrt(SquaredLength());
	}
	inline void Vector3::Normalize()
	{
		Single num2 = SquaredLength();
		shh_assert(num2 != 0.0f);
		Single num = 1.0f / ((Single) Math::Sqrt(num2));		
		x *= num;
		y *= num;
		z *= num;
	}

	inline Single Vector3::DistanceSquared(const Vector3& value1, const Vector3& value2)
	{
		float num3 = value1.x - value2.x;
		float num2 = value1.y - value2.y;
		float num = value1.z - value2.z;
		return (((num3 * num3) + (num2 * num2)) + (num * num));
	}
	inline Single Vector3::Distance(const Vector3& value1, const Vector3& value2)
	{
		return Math::Sqrt(DistanceSquared(value1, value2));
	}
	inline Single Vector3::Dot(const Vector3& value1, const Vector3& value2)
	{
		return (((value1.x * value2.x) + (value1.y * value2.y)) + (value1.z * value2.z));
	}
	inline Vector3 Vector3::Cross(const Vector3& value1, const Vector3& value2)
	{
		return Vector3(
			(value1.y * value2.z) - (value1.z * value2.y),
			(value1.z * value2.x) - (value1.x * value2.z),
			(value1.x * value2.y) - (value1.y * value2.x));
	}
	inline void Vector3::Max(const Vector3& value1, const Vector3& value2, Vector3& result)
	{
		result.x = (value1.x > value2.x) ? value1.x : value2.x;
		result.y = (value1.y > value2.y) ? value1.y : value2.y;
		result.z = (value1.z > value2.z) ? value1.z : value2.z;

	}
	inline void Vector3::Min(const Vector3& value1, const Vector3& value2, Vector3& result)
	{
		result.x = (value1.x < value2.x) ? value1.x : value2.x;
		result.y = (value1.y < value2.y) ? value1.y : value2.y;
		result.z = (value1.z < value2.z) ? value1.z : value2.z;

	}

}