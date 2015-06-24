
#include "SharedObject.h"

namespace Shh
{

	SharedObject::SharedObject() 
		:mRefCount(Invalid_Count)
	{
 
	}

	SharedObject::~SharedObject()
	{
		shh_assert(0 == this->mRefCount);
	}


}