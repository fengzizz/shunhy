
#include "Core/SharedObject.h"
#include "DrawDrv/InputLayout.h"
#include "Renderer/Renderer.h"
#include "GraphicInstance.h"
#include "Graphics.h"

namespace Shh
{

	RenderHandle::RenderHandle()
		:mResource(nullptr)
	{

	}

	bool RenderHandle::IsValid() const
	{
		if (nullptr != mResource)
		{
			return mResource->Valid();
		}
		return false;
	}

	bool RenderHandle::IsNull() const
	{
		return nullptr == mResource;
	}

	GraphicInstanceCode RenderHandle::Code() const
	{
		if (nullptr != mResource)
		{
			return mResource->GetCode();
		}
		return GraphicInstanceCode::Unknown;
	}

}
