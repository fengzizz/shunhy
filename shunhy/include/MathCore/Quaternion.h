#pragma once
//#include "MathCoreDef.h"
#include "OthersDef.h"
#include "MathCore.h" 

namespace Shh
{
	
	inline void Quaternion::Normalize()
	{
		Single num2 = (((vx * vx) + (vy * vy)) + (vz * vz)) + (w * w);
		Single num = 1.0f / Math::Sqrt(num2);
		vx *= num;
		vy *= num;
		vz *= num;
		w *= num;
	}
	inline Quaternion Quaternion::Slerp(const Quaternion& value1, const Quaternion& value2, Single amount)
	{
		Single num2;
		Single num3;
		Quaternion quaternion;
		Single num = amount;
		Single num4 = (((value1.vx * value2.vx) + (value1.vy * value2.vy)) + (value1.vz * value2.vz)) + (value1.w * value2.w);
		bool flag = false;
		if (num4 < 0.0f)
		{
			flag = true;
			num4 = -num4;
		}
		if (num4 > 0.999999f)
		{
			num3 = 1.0f - num;
			num2 = flag ? -num : num;
		}
		else
		{
			Single num5 = Math::ACos(num4);
			Single num6 = (1.0f / Math::Sin( num5));
			num3 = ( Math::Sin(((1.0f - num) * num5))) * num6;
			num2 = flag ? (( - Math::Sin((num * num5))) * num6) : ((Math::Sin(num * num5)) * num6);
		}
		quaternion.vx = (num3 * value1.vx) + (num2 * value2.vx);
		quaternion.vy = (num3 * value1.vy) + (num2 * value2.vy);
		quaternion.vz = (num3 * value1.vz) + (num2 * value2.vz);
		quaternion.w = (num3 * value1.w) + (num2 * value2.w);
		return quaternion;

	}
}