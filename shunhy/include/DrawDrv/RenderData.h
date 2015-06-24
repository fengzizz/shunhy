
#ifndef __RENDERDATA_H__
#define __RENDERDATA_H__
#include "DrawDrv/InputElement.h"
namespace Shh
{
	const int MaxNumVertexStreams = 2;
	typedef std::vector<InputElement> InputElements;


	struct _Shh_Export RenderData
	{
		SourceUsage usage;
	protected:
		inline RenderData(SourceUsage _usage)
			:usage(_usage)
		{

		}
	};
	struct _Shh_Export RenderDataStream
	{
		void* data;
		int sizeInByte;
		inline RenderDataStream()
			:data(nullptr)
			,sizeInByte(0)
		{

		}
	};

	struct _Shh_Export VertexStream
	{
		pointer data;
		int offsetInByte;
		int elemSizeInByte;
		inline VertexStream()
			:data(nullptr)
			,offsetInByte(0)
			,elemSizeInByte(0)
		{

		}
	};
	typedef std::vector<VertexStream> VertexStreams;

	struct _Shh_Export VertexBufferData : public RenderData
	{
		struct Vertex
		{
			InputElements vertexComponents;
			VertexStreams vertexComponentStreams;
		};
		Vertex vertex;
		//VertexStream uniqueStream;
		PrimitieTopology topology;
		int vertexCount;
		inline VertexBufferData()
			: RenderData(SourceUsage::Immutable)
			, topology(PrimitieTopology::Unknown)
		{

		}
	};

	typedef pointer IndexStream;
	struct _Shh_Export IndexBufferData : public RenderData
	{
		int indexCount;
		IndexBufferFormat format;
		IndexStream stream;
		inline IndexBufferData()
			: RenderData(SourceUsage::Immutable)
			, indexCount(0)
			, stream(nullptr)
			, format(IndexBufferFormat::Unknown)
		{

		}
	};

	struct _Shh_Export VERTEX_DESC
	{
		SourceUsage usage;
		PrimitieTopology topology;
		int vertexCount;
		int vertexSizeInbyte;
	};
	struct _Shh_Export INDEX_DESC
	{
		SourceUsage usage;
		IndexBufferFormat format;
		int indexCount;
	};

	struct _Shh_Export TEXTURE_DESC
	{
		int width;
		int height;
		int depth;
		int numMipLevels;
		PixelFormat pixelFormat;
	};

	void CopyVertexDataToGraphicBuffer(pointer dest, const VertexBufferData& source, int strides);
	int CalculateVertexStrides(const InputElements& inputs);
}


#endif	//__RENDERDATA_H__