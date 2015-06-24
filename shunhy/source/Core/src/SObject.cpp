
#include "SObject.h"

namespace Shh
{
	static volatile long IDCounter = 0;
	SObject::SObject()
	{
		_id = _Increment(IDCounter);
	}

	SObject::~SObject()
	{

	}
}

