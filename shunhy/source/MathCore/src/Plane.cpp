#include "Plane.h"

namespace Shh
{
	Plane Plane::CreateFromPoints(const Vector3& point1, const Vector3& point2, const Vector3& point3)
	{
		Single num10 = point2.x - point1.x;
		Single num9 = point2.y - point1.y;
		Single num8 = point2.z - point1.z;
		Single num7 = point3.x - point1.x;
		Single num6 = point3.y - point1.y;
		Single num5 = point3.z - point1.z;
		Single num4 = (num9 * num5) - (num8 * num6);
		Single num3 = (num8 * num7) - (num10 * num5);
		Single num2 = (num10 * num6) - (num9 * num7);
		Single num11 = ((num4 * num4) + (num3 * num3)) + (num2 * num2);
		Single num = 1.0f / ( Math::Sqrt(num11));
		Plane plane;
		plane.normal.x = num4 * num;
		plane.normal.y = num3 * num;
		plane.normal.z = num2 * num;
		plane.d = -(((plane.normal.x * point1.x) + (plane.normal.y * point1.y)) + (plane.normal.z * point1.z));
		return plane;
	}
}