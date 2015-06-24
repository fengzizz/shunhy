#include "FileSystem/PathAssign.h"

namespace Shh
{
	const String PathAssign::HomeKey = "home";
	const String PathAssign::FullKey = "full";
	PathAssign::PathAssign()
	{
		mAssignMap[HomeKey] = "";
	}

	PathAssign::~PathAssign()
	{

	}

	void PathAssign::SetAssign(const String& key, const String& pathName)
	{
		mAssignMap[key] = pathName;
	}

	bool PathAssign::Contain(const String& key) const
	{
		return mAssignMap.end() != mAssignMap.find(key);
	}

	const String& PathAssign::Get(const String& key) const
	{
		return mAssignMap.at(key);
	}

}