#ifndef __RECTMODELING_H__
#define __RECTMODELING_H__
#include "MathCore/Modeling/Modeling.h"
#include "MathCore/MathCoreDef.h"
namespace Shh
{
	// ===================================
	// ====== 0 --- 1 ==================
	// ====== |  /  | ==================
	// ====== 2 --- 3 ==================
	// ===================================

	namespace Modeling
	{
		#define PARALLELOGRAM_VERTEX_COUNT 4
		#define PARALLELOGRAM_INDEX_COUNT 6

		inline size_t ParallelogramVertexCount()
		{
			return PARALLELOGRAM_VERTEX_COUNT;
		}

		inline size_t ParallelogramIndexCount()
		{
			return PARALLELOGRAM_INDEX_COUNT;
		}
		 void _Shh_Export  SetParallelogram(void* vertices, size_t vertex_size, const Vector3& top, const Vector3& right, const Vector3& center, 
			 size_t position_bias);

		 void _Shh_Export  SetParallelogram(void* vertices, size_t vertex_size, const Vector3& top, const Vector3& right, const Vector3& center, 
			 size_t position_bias, size_t normal_bias);

		template<typename Vertex>
		inline void SetParallelogram(Vertex* vertices, const Vector3& top, const Vector3& right, const Vector3& center, 
			size_t position_bias)
		{
			SetParallelogram(vertices, sizeof(Vertex), top, right, center, position_bias);
		}

		template<typename Vertex>
		inline void SetParallelogram(Vertex* vertices, const Vector3& top, const Vector3& right, const Vector3& center, 
			size_t position_bias, size_t normal_bias)
		{
			SetParallelogram(vertices, sizeof(Vertex), top, right, center, position_bias, normal_bias);
		}
	}

}

#endif //__RECTMODELING_H__