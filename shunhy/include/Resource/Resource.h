#ifndef __RESOURCE_H__
#define __RESOURCE_H__
#include "Resource/ResourceDef.h"
#include "Resource/NameObject.h"
namespace Shh
{
	typedef NameString ResourceURI;//临时。
	class _Shh_Export Resource : public NameObject
	{
	public:
		virtual ~Resource();

		void _SetURI(const ResourceURI& uri);
	protected:
		Resource();
		ResourceURI mURI;
	};

	inline void Resource::_SetURI(const ResourceURI& uri)
	{
		mURI = uri;
	}
}


#endif //__RESOURCE_H__