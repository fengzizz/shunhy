#include "MathCore/Modeling/ParallelogramModeling.h"
#include "ModelingPrivate.h"
#include "Vector3.h"
namespace Shh
{
	namespace Modeling
	{
		void SetParallelogram(void* vertices, size_t vertex_size, const Vector3& top, const Vector3& right, const Vector3& center, 
			size_t position_bias)
		{
			shh_assert(vertex_size >= sizeof(Vector3));
			//std::vector<float>::iterator
			_elem_iterator<Vector3> elem(_bias_in_bytes(vertices, position_bias), vertex_size);
			*(elem) = center + top - right;//0
			*(++elem) = center + top + right;//1
			*(++elem) = center - top - right;//2
			*(++elem) = center - top + right;//3
		}

		void SetParallelogram(void* vertices, size_t vertex_size, const Vector3& top, const Vector3& right, const Vector3& center,
			size_t position_bias, size_t normal_bias)
		{
			shh_assert(vertex_size >= sizeof(Vector3) * 2);
			SetParallelogram(vertices, vertex_size, top, right, center, position_bias);
			Vector3 normal = Vector3::Cross(right, top);
			normal.Normalize();
			_elem_iterator<Vector3> normal_elem(_bias_in_bytes(vertices, normal_bias), vertex_size);
			*normal_elem = normal;
			*(++normal_elem) = normal;
			*(++normal_elem) = normal;
			*(++normal_elem) = normal;
		}
	}
}