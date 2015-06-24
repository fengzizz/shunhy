#ifndef __RENDERHANDLE_H__
#define __RENDERHANDLE_H__
#include "Core/TEnum.h"
#include "Core/SharedObject.h"
#include "DrawDrv/RenderFormat.h"
#include "Renderer/RendererDef.h"
#include "Graphics/GraphicsDef.h"


namespace Shh
{
	class GraphicInstanceCode
	{
		__Declare_Enum
		{
			Unknown = 0,
				Primitive,
				Shader,
				Texture,
				RenderTarget,
		};
		__Declare_Enum_Struct(GraphicInstanceCode, 0);
	};

	class GraphicInstance : public SharedObject
	{
	public:
		virtual ~GraphicInstance() {};
		virtual bool Valid() const = 0;
		virtual GraphicInstanceCode GetCode() const = 0;
	private:
	};



	class _Shh_Export RenderHandle
	{
	public:
		RenderHandle();
		bool IsValid() const;
		bool IsNull() const;
		GraphicInstanceCode Code() const;
		friend class GraphicResourceTool;
	private:
		GraphicInstance* mResource;
	};


	typedef RenderHandle GPUProgramHandle;
	typedef RenderHandle TextureHandle;
	typedef RenderHandle PrimitiveHandle;
}


#endif //__RENDERHANDLE_H__