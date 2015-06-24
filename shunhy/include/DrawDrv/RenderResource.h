#ifndef __RENDERRESOURCE_H__
#define __RENDERRESOURCE_H__
//#include "Core/SharedObject.h"
namespace Shh
{

	class _Shh_Export RenderResource //: public SharedObject
	{
	public:		
		virtual ~RenderResource() {};
		virtual bool Valid() const = 0;
	private:
	};
}

#endif //__RENDERRESOURCE_H__