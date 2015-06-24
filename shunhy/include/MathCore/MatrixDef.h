#pragma once
#include "MathCoreDef.h"
#include "VectorDef.h"
namespace Shh
{
	class _Shh_Export _M4
	{
	protected:
		Single m4[4];
	public:
		Single& operator [] ( size_t index );
		const Single& operator [] (size_t index) const;
	};	
	inline Single& _M4::operator[] (size_t index)
	{
		shh_assert(index < 4);
		return m4[index];
	}
	inline const Single& _M4::operator[] (size_t index) const
	{
		shh_assert(index < 4);
		return m4[index];
	}

	class _Shh_Export _M3
	{
	protected:
		Single m3[3];
	public:
		Single& operator [] ( size_t index );
		const Single& operator [] ( size_t index ) const;
	};	

	inline Single& _M3::operator[] (size_t index)
	{
		shh_assert(index < 3);
		return m3[index];
	}
	inline const Single& _M3::operator[] (size_t index) const
	{
		shh_assert(index < 3);
		return m3[index];
	}

	class _Shh_Export Matrix4
	{
	public:
		typedef Single ValueType;
		Matrix4();
		Matrix4(
			Single m00, Single m01, Single m02, Single m03,
			Single m10, Single m11, Single m12, Single m13,
			Single m20, Single m21, Single m22, Single m23,
			Single m30, Single m31, Single m32, Single m33);
		_M4& operator[] (size_t index);
		const _M4& operator[] (size_t index) const;
		Matrix4 operator + ( const Matrix4 &mat4 ) const;
		Matrix4 operator - ( const Matrix4 &mat4 ) const;
		Matrix4 operator * (const Matrix4 &mat4) const;
		Matrix4 operator * (const Matrix43 &mat43) const;
		Matrix4 operator * (const Matrix34 &mat34) const;
		Matrix4 operator * (const Matrix3 &mat33) const;

		static const Matrix4 Zero;
		static const Matrix4 Identity;
		static const Matrix4 ClipSpace2DToImageSpace;

		static const int ElementCount;
		static const int ElementSize;
		static const int SizeInByte;

	protected:
		union 
		{
			_M4 m44[4];
			Single _m44[16];
		};
	};
	inline Matrix4::Matrix4()
	{

	}
	inline Matrix4::Matrix4( Single m00, Single m01, Single m02, Single m03,
		Single m10, Single m11, Single m12, Single m13, 
		Single m20, Single m21, Single m22, Single m23, 
		Single m30, Single m31, Single m32, Single m33 )
	{
		_m44[0] = m00;
		_m44[1] = m01;
		_m44[2] = m02;
		_m44[3] = m03;
		_m44[4] = m10;
		_m44[5] = m11;
		_m44[6] = m12;
		_m44[7] = m13;
		_m44[8] = m20;
		_m44[9] = m21;
		_m44[10] = m22;
		_m44[11] = m23;
		_m44[12] = m30;
		_m44[13] = m31;
		_m44[14] = m32;
		_m44[15] = m33;

	}
	inline _M4& Matrix4::operator[] (size_t index)
	{
		shh_assert(index < 4);
		return m44[index];
	}
	inline const _M4& Matrix4::operator[] (size_t index) const
	{
		shh_assert(index < 4);
		return m44[index];
	}

	class _Shh_Export Matrix3
	{
	public:
		typedef Single ValueType;
		Matrix3();
		Matrix3(
			Single m00, Single m01, Single m02,
			Single m10, Single m11, Single m12,
			Single m20, Single m21, Single m22);	

		_M3& operator[](size_t index);
		const _M3& operator[](size_t index) const;
		Matrix3 operator + (const Matrix3& mat) const;
		Matrix3 operator - (const Matrix3& mat) const;
		Matrix3 operator * (const Matrix3& mat3) const;
		Matrix4 operator * (const Matrix4& mat4) const;
		Matrix43 operator * (const Matrix43& mat43) const;

		static const Matrix3 Zero;
		static const Matrix3 Identity;

		static const int ElementCount;
		static const int ElementSize;
		static const int SizeInByte;

	protected:
		union 
		{
			_M3 m33[3];
			Single _m33[9];
		};
	};
	inline Matrix3::Matrix3()
	{

	}
	inline Matrix3::Matrix3( Single m00, Single m01, Single m02,
		Single m10, Single m11, Single m12, 
		Single m20, Single m21, Single m22 )
	{
		_m33[0] = m00;
		_m33[1] = m01;
		_m33[2] = m02;

		_m33[3] = m10;
		_m33[4] = m11;
		_m33[5] = m12;

		_m33[6] = m20;
		_m33[7] = m21;
		_m33[8] = m22;

	}
	inline _M3& Matrix3::operator[] (size_t index)
	{
		shh_assert(index < 3);
		return m33[index];
	}
	inline const _M3& Matrix3::operator[] (size_t index) const
	{
		shh_assert(index < 3);
		return m33[index];
	}

	class _Shh_Export Matrix43
	{
	public:
		typedef Single ValueType;
		Matrix43();
		Matrix43(
			Single m00, Single m01, Single m02,
			Single m10, Single m11, Single m12,
			Single m20, Single m21, Single m22,
			Single m30, Single m31, Single m32);
		Matrix43 operator + (const Matrix43 &mat) const;
		Matrix43 operator - (const Matrix43 &mat) const;
		Matrix43 operator * (const Matrix43 &mat) const;
		Matrix4 operator * (const Matrix4 &mat) const;

		_M3& operator[] (size_t index);
		const _M3& operator[] (size_t index) const;
		static const Matrix43 Zero;
		static const Matrix43 Identity;

		static const int ElementCount;
		static const int ElementSize;
		static const int SizeInByte;
	protected:
		union 
		{
			_M3 m43[4];
			Single _m43[12];
		};
	};
	inline Matrix43::Matrix43()
	{

	}
	inline Matrix43::Matrix43(
		Single m00, Single m01, Single m02,
		Single m10, Single m11, Single m12,
		Single m20, Single m21, Single m22,
		Single m30, Single m31, Single m32)
	{
		_m43[0] = m00;
		_m43[1] = m01;
		_m43[2] = m02;

		_m43[3] = m10;
		_m43[4] = m11;
		_m43[5] = m12;

		_m43[6] = m20;
		_m43[7] = m21;
		_m43[8] = m22;

		_m43[9] = m30;
		_m43[10] = m31;
		_m43[11] = m32;

	}
	inline _M3& Matrix43::operator[] (size_t index)
	{
		shh_assert(index < 4);
		return m43[index];
	}
	inline const _M3& Matrix43::operator[] (size_t index) const
	{
		shh_assert(index < 4);
		return m43[index];
	}

	class _Shh_Export Matrix34
	{
	public:
		typedef Single ValueType;
		Matrix34();
		Matrix34(
			Single m00, Single m01, Single m02, Single m03,
			Single m10, Single m11, Single m12, Single m13,
			Single m20, Single m21, Single m22, Single m23);
		Matrix34 operator + (const Matrix34& mat) const;
		Matrix34 operator - (const Matrix34& mat) const;
		Matrix34 operator * (const Matrix34& mat) const;
		Matrix4 operator * (const Matrix4& mat) const;
		Vector3 operator * (const Vector3& vec3 ) const;

		_M4& operator[] (size_t index);
		const _M4& operator[] (size_t index) const;
		static const Matrix34 Zero;
		static const Matrix34 Identity;

		static const int ElementCount;
		static const int ElementSize;
		static const int SizeInByte;
	protected:
		union 
		{
			_M4 m34[4];
			Single _m34[12];
		};
	};

	inline Matrix34::Matrix34()
	{

	}
	inline Matrix34::Matrix34(
		Single m00, Single m01, Single m02, Single m03,
		Single m10, Single m11, Single m12, Single m13,
		Single m20, Single m21, Single m22, Single m23)
	{
		_m34[0] = m00;
		_m34[1] = m01;
		_m34[2] = m02;
		_m34[3] = m03;

		_m34[4] = m10;
		_m34[5] = m11;
		_m34[6] = m12;
		_m34[7] = m13;

		_m34[8] = m20;
		_m34[9] = m21;
		_m34[10] = m22;
		_m34[11] = m23;

	}
	inline _M4& Matrix34::operator[] (size_t index)
	{
		shh_assert(index < 4);
		return m34[index];
	}
	inline const _M4& Matrix34::operator[] (size_t index) const
	{
		shh_assert(index < 4);
		return m34[index];
	}
}