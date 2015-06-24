#ifndef __SHH_NAMEABLE_H__
#define __SHH_NAMEABLE_H__
#include "Core/U8String.h"
namespace Shh
{
	class _Shh_Export Nameable
	{
	public:
		typedef U8String Name;
		Nameable();
		Nameable(const Name& name);
		virtual ~Nameable();
		void SetName(const Name& name);
		const Name& GetName() const;
	private:
		Name mName;
	};

	inline void Nameable::SetName(const Name& name)
	{
		mName = name;
	}

	inline const Nameable::Name& Nameable::GetName() const
	{
		return mName;
	}
}
#endif //__SHH_NAMEABLE_H__