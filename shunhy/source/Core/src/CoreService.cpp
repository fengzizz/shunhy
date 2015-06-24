
#include "FileSystem/FileSystem.h"
#include "Log.h"
#include "CoreService.h"
namespace Shh
{
	SingletonInstancePtr(CoreService);

	CoreService::CoreService()
		:mFileSystem(nullptr)
	{

	}

	CoreService::~CoreService()
	{

	}

	void CoreService::Setup(const U8String& working_path)
	{
		__set_logfilename(working_path + "/game.log");

		shh_assert(nullptr == mFileSystem);
		mFileSystem = shh_new FileSystem(working_path, "File");

		PathAssign& assign = mFileSystem->GetAssign();

		assign.SetAssign("asset", "asset");
		assign.SetAssign("system", "system");

		shh_log("core server setup.");
	}

	void CoreService::Destroy()
	{
		shh_delete mFileSystem;
		mFileSystem = nullptr;
		shh_log("core server destroy.");
	}
}