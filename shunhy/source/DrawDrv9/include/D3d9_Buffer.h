#pragma once
#include "D3d9_Common.h"
#include "RenderFormat.h"
namespace Shh
{
	class D3d9Buffer : public IRelease
	{
	public:
		D3d9Buffer(SourceUsage usage);
		virtual void Release() override;
		virtual ~D3d9Buffer();
	protected:
		SourceUsage mBufferUsage;
	private:
	};
}