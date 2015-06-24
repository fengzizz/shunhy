#include "Core/Log.h"
#include "Core/Memory.h"
#include "RenderData.h"
namespace Shh
{
	void _copyVertexData(pointer dest, const VertexStream& from, int vertexStrides, int vertexCount)
	{

		//小单位的拷贝中，等号赋值比调用内存拷贝函数要快很多很多。
		//叫xmemcpy的一个工具就是这么干的，号称小于120字节以内的拷贝比gcc的内存拷贝快10倍。
		//等号赋值长度必须<=128字节，并且是机器字长的倍数

		//在渲染系统中，顶点的数据的最小单位是4byte, 即一个int32的大小
		shh_assert(vertexStrides > 0);
		shh_assert(NULL != from.data);
		shh_assert(NULL != dest);
		shh_assert((from.elemSizeInByte % 4) == 0);
		shh_assert((vertexStrides % 4) == 0);

		int data_stride4 = from.elemSizeInByte / 4;
		int vertex_stride4 = vertexStrides / 4;
		const uint32* buffer32 = (const uint32*)(from.data);
		uint32* dest32 = (uint32*)(((uint8*)dest) + from.offsetInByte);

		switch(data_stride4)
		{
		case 1:
			{		
				while(vertexCount--)
				{
					XMemory::CopyN1(buffer32, dest32);
					++buffer32;
					dest32 += vertex_stride4;
				}
				break;
			}
		case 2:
			{
				while(vertexCount--)
				{
					XMemory::CopyN2(buffer32, dest32);
					buffer32 += 2;
					dest32 += vertex_stride4;
				}
				break;
			}
		case 3:
			{
				while(vertexCount--)
				{
					XMemory::CopyN3(buffer32, dest32);
					buffer32 += 3;
					dest32 += vertex_stride4;
				}
				break;
			}
		case 4:
			{
				while(vertexCount--)
				{
					XMemory::CopyN4(buffer32, dest32);
					buffer32 += 4;
					dest32 += vertex_stride4;
				}
				break;
			}
		case 5:
			{
				while(vertexCount--)
				{
					XMemory::CopyN5(buffer32, dest32);
					buffer32 += 5;
					dest32 += vertex_stride4;
				}
				break;
			}
		case 6://VertexComponent::SkinJIndices和VertexComponent::SkinWeights是合在一起的，所以会有6的情况。
			{
				while(vertexCount--)
				{

					XMemory::CopyN6(buffer32, dest32);

					buffer32 += 6;
					dest32 += vertex_stride4;
				}
				break;
			}
		default:
			shh_error("error vertex data size");//只有以上的那几种大小
			break;
		}

	}

	void CopyVertexDataToGraphicBuffer(pointer dest, const VertexBufferData& source, int vertexStrides)
	{
		const VertexStreams& dataStreams = source.vertex.vertexComponentStreams;
		if (source.vertex.vertexComponentStreams.size() == 1
			&& source.vertex.vertexComponentStreams[0].elemSizeInByte == vertexStrides
			&& source.vertex.vertexComponentStreams[0].data)
		{
			Memory::Copy(dest, dataStreams[0].data, vertexStrides * source.vertexCount);
		}
		else
		{
			for (size_t i = 0; i < dataStreams.size(); ++i)
			{
				const VertexStream& stream = dataStreams[i];
				if (stream.data)
				{
					_copyVertexData(dest, stream, vertexStrides, source.vertexCount);
				}
			}
		}
	}

	int CalculateVertexStrides(const InputElements& inputs)
	{
		int vertexByteSize = 0;
		for (size_t i = 0; i < inputs.size(); i++)
		{
			// update the components byte offset while we're at it
			vertexByteSize += inputs[i].GetSize();
		}
		return vertexByteSize;
	}

}