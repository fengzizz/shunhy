#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "Core/SharedObject.h"
namespace Shh
{
	class _Shh_Export SObject : public SharedObject 
	{
	public:
		SObject();
		virtual ~SObject() override;
		long GetID() const;
	private:
		long _id;
	};

	inline long SObject::GetID() const
	{
		return _id;
	}
}

#endif //__OBJECT_H__
