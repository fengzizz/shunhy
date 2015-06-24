#pragma once
#include "OthersDef.h"
#include "Vector3.h"

namespace Shh
{
	class _Shh_Export Plane//
	{
	public:
		Plane();
		Plane(Single a, Single b, Single c, Single d);
		Plane(const Vector3& normal, Single d);
		Plane(const Vector4& vec4);	

		static Plane CreateFromPoints(const Vector3& point1, const Vector3& point2, const Vector3& point3);

		Vector3 normal;	//法线
		Single d;		//平面沿法线的反方向到原点的距离
	};
	inline Plane::Plane()
	{

	}
	inline Plane::Plane(Single a, Single b, Single c, Single d)
	{
		normal.x = a;
		normal.y = b;
		normal.z = c;
		this->d = d;
	}

	inline Plane::Plane(const Vector3& normal, Single d)
	{
		this->normal = normal;
		this->d = d;
	}
	inline Plane::Plane(const Vector4& vec4)
	{
		normal.x = vec4.x;
		normal.y = vec4.y;
		normal.z = vec4.z;
		d = vec4.w;
	}
}