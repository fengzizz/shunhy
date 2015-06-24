#pragma once
#include "BoundingBox.h"
//#include <algorithm>

namespace Shh
{
	 ContainmentType BoundingBox::Contains(const BoundingBox& box) const
	 {
		 if ((max.x < box.min.x) || (min.x > box.max.x))
		 {
			 return CT_Disjoint;
		 }
		 if ((max.y < box.min.y) || (min.y > box.max.y))
		 {
			 return CT_Disjoint;
		 }
		 if ((max.z < box.min.z) || (min.z > box.max.z))
		 {
			 return CT_Disjoint;
		 }
		 if ((((min.x <= box.min.x) && (box.max.x <= max.x)) && ((min.y <= box.min.y) && (box.max.y <= max.y))) && ((min.z <= box.min.z) && (box.max.z <= max.z)))
		 {
			 return CT_Contains;
		 }
		 return CT_Intersects;

	 }
	 ContainmentType BoundingBox::Contains(const Vector3& point) const
	 {
		 if ((((min.x <= point.x) && (point.x <= max.x)) && ((min.y <= point.y) && (point.y <= max.y))) && ((min.z <= point.z) && (point.z <= max.z)))
		 {
			 return CT_Contains;
		 }
		 return CT_Disjoint;
	 }

	 bool BoundingBox::Intersects(const BoundingBox& box) const
	 {
		 if ((max.x < box.min.x) || (min.x > box.max.x))
		 {
			 return false;
		 }
		 if ((max.y < box.min.y) || (min.y > box.max.y))
		 {
			 return false;
		 }
		 return ((max.z >= box.min.z) && (min.z <= box.max.z));
	 }
	BoundingBox BoundingBox::CreateFromPoints(const std::vector<Vector3>& point_list)
	{
		shh_assert(0 < point_list.size());
		Vector3 min(Float_Max);
		Vector3 max(Float_Min);//std::vector<Vector3>::const_iterator
		for (auto first = point_list.begin(); first != point_list.end(); ++first)
		{
			//Vector3 vector4 = first;
			Vector3::Min(min, *first, min);
			Vector3::Max(max, *first, max);
		}
		return BoundingBox(min, max);
	}
	BoundingBox BoundingBox::CreateFromPoints(Vector3* src_begin, size_t count)
	{
		shh_assert(0 < count);
		shh_assert(nullptr != src_begin);
		Vector3 min(Float_Max);
		Vector3 max(Float_Min);
		while(count)
		{
			--count;
			Vector3* vec = src_begin + count;
			Vector3::Min(min, *vec, min);
			Vector3::Max(max, *vec, max);
		}
		return BoundingBox(min, max);
	}
}