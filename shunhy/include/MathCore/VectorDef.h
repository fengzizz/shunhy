#pragma once
#include "MathCoreDef.h"

namespace Shh
{
	class _Shh_Export Vector2
	{
	public:
		typedef Single ValueType;
		Vector2();		
		Vector2(Single fx, Single fy);
		Vector2(int nx, int ny);
		explicit Vector2(Single f);
		explicit Vector2(const Single coordinate[2]);
		explicit Vector2(const int coordinate[2]);

		Vector2 operator +(const Vector2& vec2) const;
		Vector2 operator -(const Vector2& vec2) const;
		Vector2 operator *(const Vector2& vec2) const;
		Vector2 operator *(Single scale) const;
		friend Vector2 operator *(Single scale, const Vector2& vec2);
		Vector2 operator /(Single scale) const;
		Vector2 operator /(const Vector2& vec2) const;
		Vector2& operator +=(const Vector2& vec2);
		Vector2& operator -=(const Vector2& vec2);
		Vector2& operator *=(const Vector2& vec2);
		Vector2& operator *=(Single vec2);
		Vector2& operator /=(const Vector2& vec2);
		Vector2& operator /=(Single vec2);
		Vector2 operator -() const;
		bool operator ==(const Vector2& vec2) const;
		bool operator !=(const Vector2& vec2) const;

		Single SquaredLength() const;
		Single Length() const;
		void Normalize();
		
		
		static Single Distance(const Vector2& value1, const Vector2& value2);
		static Single DistanceSquared(const Vector2& value1, const Vector2& value2);
		static Single Dot(const Vector2& value1, const Vector2& value2);

		static const Vector2 Zero;
		static const Vector2 Unit_X;
		static const Vector2 Unit_Y;
		static const Vector2 One;

		static const int ElementCount;
		static const int ElementSize;
		static const int SizeInByte;

		Single x, y;
	};

	inline Vector2::Vector2()
	{

	}
	inline Vector2::Vector2(Single f)
		: x(f), y(f)
	{

	}
	inline Vector2::Vector2(Single fx, Single fy)
		:x(fx),y(fy)
	{

	}
	inline Vector2::Vector2(int nx, int ny)
		:x((Single)nx), y((Single)ny)
	{

	}
	inline Vector2::Vector2(const Single coordinate[2])
		:x(coordinate[0]),y(coordinate[1])
	{

	}
	inline Vector2::Vector2(const int coordinate[2])
		:x((Single)coordinate[0]),y((Single)coordinate[1])
	{

	}

	class _Shh_Export Vector3
	{
	public:
		typedef Single ValueType;
		Vector3();

		Vector3(Single fx, Single fy, Single fz);
		Vector3(int nx, int ny, int nz);
		explicit Vector3(const Vector2& vec2,Single f = 1.0f);
		explicit Vector3(Single f);
		explicit Vector3(const Single coordinate[3]);	

		Vector3 operator +(const Vector3& vec3) const;
		Vector3 operator -(const Vector3& vec3) const;
		Vector3 operator *(const Vector3& vec3) const;
		Vector3 operator *(Single scale) const;
		friend Vector3 operator *(Single scale, const Vector3& vec3);
		Vector3 operator /(const Vector3& vec3) const;
		Vector3 operator /(Single scale) const;
		Vector3& operator +=(const Vector3& value);
		Vector3& operator -=(const Vector3& value);
		Vector3& operator *=(const Vector3& value);
		Vector3& operator *=(Single value);
		Vector3& operator /=(const Vector3& value);
		Vector3& operator /=(Single value);
		Vector3 operator -() const;
		bool operator ==(const Vector3& vec3) const;
		bool operator !=(const Vector3& vec3) const;

		Vector3 operator * (const Matrix4& mat4) const;
		Vector3 operator * (const Matrix43& mat43) const;
		Vector3 operator * (const Matrix3& mat3) const;

		void Transform(const Matrix4& mat4);
		void Transform(const Matrix3& mat3);
		void Transform(const Matrix43& mat43);

		Single SquaredLength() const;
		Single Length() const;
		void Normalize();

		static Single Distance(const Vector3& value1, const Vector3& value2);
		static Single DistanceSquared(const Vector3& value1, const Vector3& value2);
		static Single Dot(const Vector3& value1, const Vector3& value2);
		static Vector3 Cross(const Vector3& value1, const Vector3& value2);
		static void Max(const Vector3& value1, const Vector3& value2, Vector3& result);
		static void Min(const Vector3& value1, const Vector3& value2, Vector3& result);

		static const Vector3 Zero;
		static const Vector3 Unit_X;
		static const Vector3 Unit_Y;
		static const Vector3 Unit_Z;
		static const Vector3 One;

		static const int ElementCount;
		static const int ElementSize;
		static const int SizeInByte;

		Single x, y, z;
	};

	inline Vector3::Vector3()
	{

	}
	inline Vector3::Vector3(Single f)
		:x(f), y(f), z(f)
	{

	}
	inline Vector3::Vector3(Single fx, Single fy, Single fz)
		:x(fx), y(fy), z(fz)
	{

	}
	inline Vector3::Vector3(int nx, int ny, int nz)
		:x((Single)nx), y((Single)ny), z((Single)nz)
	{

	}
	inline Vector3::Vector3(const Vector2& vec2,Single f)
		:x(vec2.x), y(vec2.y), z(f)
	{

	}
	inline Vector3::Vector3(const Single coordinate[3])
		:x(coordinate[0]), y(coordinate[1]), z(coordinate[2]) 
	{

	}

	class _Shh_Export Vector4
	{
	public:
		typedef Single ValueType;
		Vector4();		
		Vector4(Single fx, Single fy, Single fz, Single fw);
		Vector4(int nx, int ny, int nz, int nw);
		Vector4(const Vector2& vec2, Single fz, Single fw);
		explicit Vector4(const Vector3& vec3, Single fw = 1.0f);
		explicit Vector4(Single f);
		explicit Vector4(const Single coordinate[4]);

		Vector4 operator + (const Vector4& vec4) const;
		Vector4 operator - (const Vector4& vec4) const;
		Vector4 operator * (const Vector4& vec4) const;
		Vector4 operator * (Single scale);
		friend Vector4 operator * (Single scale, const Vector4& vec4);
		Vector4 operator / (const Vector4& vec4) const;
		Vector4 operator / (Single scale) const;
		Vector4& operator += (const Vector4& vec4);
		Vector4& operator -= (const Vector4& vec4);
		Vector4& operator *= (const Vector4& vec4);
		Vector4& operator *= (Single vec4);
		Vector4& operator /= (const Vector4& vec4);
		Vector4& operator /= (Single vec4);
		Vector4 operator - () const;
		bool operator == (const Vector4& vec4) const;
		bool operator != (const Vector4& vec4) const;

		Vector4 operator * (const Matrix4& mat4) const;
		Vector4 operator * (const Matrix43& mat43) const;
		Vector4 operator * (const Matrix3& mat3) const;

		Single SquaredLength() const;
		Single Length() const;
		void Normalize();
		

		void Transform(const Matrix4& mat4);
		void Transform(const Matrix43& mat43);
		void Transform(const Matrix3& mat3);

		static Single Distance(const Vector4& value1, const Vector4& value2);
		static Single DistanceSquared(const Vector4& value1, const Vector4& value2);
		static Single Dot(const Vector4& value1, const Vector4& value2);

		static const Vector4 Zero;
		static const Vector4 Unit_X;
		static const Vector4 Unit_Y;
		static const Vector4 Unit_Z;
		static const Vector4 Unit_W;
		static const Vector4 One;

		static const int ElementCount;
		static const int ElementSize;
		static const int SizeInByte;

		Single x, y, z, w;
	};

	inline Vector4::Vector4()
	{

	}
	inline Vector4::Vector4(Single f)
		:x(f), y(f), z(f), w(f)
	{

	}
	inline Vector4::Vector4(Single fx, Single fy, Single fz, Single fw)
		:x(fx), y(fy), z(fz), w(fw)
	{

	}
	inline Vector4::Vector4(int nx, int ny, int nz, int nw)
		:x((Single)nx), y((Single)ny), z((Single)nz), w((Single)nw)
	{

	}
	inline Vector4::Vector4(const Vector2& vec2, Single fz, Single fw)
		:x(vec2.x), y(vec2.y), z(fz), w(fw)
	{

	}
	inline Vector4::Vector4(const Vector3& vec3, Single fw)
		:x(vec3.x), y(vec3.y), z(vec3.z), w(fw)
	{

	}
	inline Vector4::Vector4(const Single coordinate[4])
		:x(coordinate[0]), y(coordinate[1]), z(coordinate[2]), w(coordinate[3])
	{

	}

}