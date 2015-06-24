#ifndef __NAME_OBJECT_H__
#define __NAME_OBJECT_H__

#include "Core/SObject.h"
#include "Core/HString.h"

namespace Shh
{
	//以后应该要做成静态的字符串，现在将就一下。
	class _Shh_Export NameString : public HString
	{
	public:
		static inline NameString from(const U8String& str)
		{
			NameString ns;
			ns.set(str);
			return ns;
		}
	};

	class _Shh_Export NameObject : public SObject
	{
	public:
		NameObject();
		virtual ~NameObject() override;
		void SetName(const NameString& name);
		const NameString& GetName() const;
	private:
		NameString mName;
	};

	inline void NameObject::SetName(const NameString& name)
	{
		mName = name;
	}

	inline const NameString& NameObject::GetName() const
	{
		return mName;
	}
}
#endif //__NAME_OBJECT_H__
