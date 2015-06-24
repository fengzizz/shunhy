#ifndef __GRAPHICRESOURCE_H__
#define __GRAPHICRESOURCE_H__
#include "Core/SharedObject.h"
#include "DrawDrv/VertexBuffer.h"
#include "DrawDrv/GPUProgram.h"
#include "Graphics/Graphics.h"
namespace Shh
{
#define __ResourceCode(_code) \
public: \
	static const GraphicInstanceCode::Enum Code = _code;\
	virtual GraphicInstanceCode GetCode() const\
	{\
		return Code;\
	}\
private:\


	template<typename _Ty>
	class GraphicInstanceTmpl : public GraphicInstance
	{
	public:
		typedef _Ty ResourceType;
		GraphicInstanceTmpl()
			:mResource(nullptr)
		{
		}
		virtual bool Valid() const
		{
			return nullptr != mResource;
		}

		ResourceType* GetResource() const
		{
			return static_cast<ResourceType*>(mResource);
		}
		void SetResource(ResourceType* resource)
		{
			mResource = resource;
		}
	protected:

	private:
		RenderResource* mResource;
	};

	class ShaderInstance : public GraphicInstanceTmpl<GPUProgram>
	{
		__Super(GraphicInstanceTmpl<GPUProgram>);
		__ResourceCode(GraphicInstanceCode::Shader);
	public:
	};

	class PrimitiveInstance : public GraphicInstanceTmpl<VertexBuffer>
	{
		__Super(GraphicInstanceTmpl<VertexBuffer>);
		__ResourceCode(GraphicInstanceCode::Primitive);
	public:
		IndexBuffer* GetIndexBuffer() const;
		InputLayout* GetInputLayout() const;
		PrimitieTopology GetTopology() const;
		void SetIndexBuffer(IndexBuffer* buffer);
		void SetInputLayout(InputLayout* layout);
		void SetPrimitiveTopology(PrimitieTopology topology);
		PrimitiveInstance();
	private:
		IndexBuffer* mIndexBuffer;
		InputLayout* mInputLayout;
		PrimitieTopology mTopology;
	};

	inline IndexBuffer* PrimitiveInstance::GetIndexBuffer() const
	{
		return mIndexBuffer;
	}
	inline InputLayout* PrimitiveInstance::GetInputLayout() const
	{
		return mInputLayout;
	}
	inline PrimitieTopology PrimitiveInstance::GetTopology() const
	{
		return mTopology;
	}

	inline void PrimitiveInstance::SetIndexBuffer(IndexBuffer* buffer)
	{
		mIndexBuffer = buffer;
	}

	inline void PrimitiveInstance::SetInputLayout(InputLayout* layout)
	{
		mInputLayout = layout;
	}

	inline void PrimitiveInstance::SetPrimitiveTopology(PrimitieTopology topology)
	{
		mTopology = topology;
	}



}
#endif //__GRAPHICRESOURCE_H__