#ifndef __SHAREDPTR_H__
#define __SHAREDPTR_H__
#include <memory>

namespace Shh
{
#define SharedPtr std::shared_ptr

#define __DefSharedPtr(x) typedef SharedPtr<x> x##Ptr;\
	typedef std::weak_ptr<x> x##WeakPtr
}

#endif//__SHAREDPTR_H__