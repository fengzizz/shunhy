#pragma once
#include "MathCoreDef.h"

namespace Shh
{
	class _Shh_Export Quaternion
	{
	public:
		typedef Single ValueType;
		Quaternion();
		Quaternion(Single fw, Single fx, Single fy, Single fz);

		static Quaternion Slerp(const Quaternion& value1, const Quaternion& value2, Single amount);
		void Normalize();

		static const Quaternion Identity;
		static const int ElementCount;
		static const int ElementSize;
		static const int SizeInByte;
		Single w, vx, vy, vz;

	};
	inline Quaternion::Quaternion()
	{

	}
	inline Quaternion::Quaternion(Single fw, Single fx, Single fy, Single fz)
		: vx(fz), vy(fx), vz(fy), w(fw)
	{

	}

	enum ContainmentType
	{
		CT_Disjoint,
		CT_Contains,
		CT_Intersects
	};
}