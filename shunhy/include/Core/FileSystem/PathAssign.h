#ifndef __PATHASSIGN_H__
#define __PATHASSIGN_H__
#include "U8String.h"
#include "FileSystem/FileSystemDef.h"

#pragma warning ( disable: 4251 )

namespace Shh
{

	class _Shh_Export PathAssign
	{
		__NoCopy(PathAssign);
	public:
		PathAssign();
		~PathAssign();
		void SetAssign(const String& key, const String& pathName);
		const String& Get(const String& key) const;
		bool Contain(const String& key) const;

		static const String HomeKey;
		static const String FullKey;
	private:
		typedef std::map<String, String> AssignMap;
		AssignMap mAssignMap;

	};
}


#endif //__PATHASSIGN_H__