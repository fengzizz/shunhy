#pragma once
#include <vector>
#include "OthersDef.h"
#include "VectorDef.h"

namespace Shh
{
	class _Shh_Export BoundingBox
	{
	public:
		BoundingBox();
		BoundingBox(const Vector3& Min, const Vector3& Max);
		ContainmentType Contains(const BoundingBox& box) const;
		ContainmentType Contains(const Vector3& box) const;
		bool Intersects(const BoundingBox& box) const;
		
		
		static BoundingBox CreateFromPoints(const std::vector<Vector3>& point_list);
		static BoundingBox CreateFromPoints(Vector3* src_begin, size_t count);

		Vector3 min;
		Vector3 max;
		
	};

	inline BoundingBox::BoundingBox()
	{

	}

	inline BoundingBox::BoundingBox(const Vector3& Min, const Vector3& Max)
		:min(Min), max(Max)
	{

	}
}