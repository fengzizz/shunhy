#ifndef __CORESERVICE_H__
#define __CORESERVICE_H__
#include "Core/Singleton.h"
#include "Core/U8String.h"
#include "Core/FileSystem/FileSystemDef.h"
namespace Shh
{
	typedef FileSystemArchive FileSystem;
	class _Shh_Export CoreService : public Singleton<CoreService>
	{
		__Dynamic_Alloc(CoreService);
	public:

		void Setup(const U8String& working_path);

		void Destroy();

		FileSystem* GetFileSystem() const;
	private:
		CoreService();
		~CoreService();
		FileSystem* mFileSystem;
	};

	inline FileSystem* CoreService::GetFileSystem() const
	{
		return mFileSystem;
	}
}

#endif //__CORESERVICE_H__