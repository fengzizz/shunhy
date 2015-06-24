
#ifndef __RENDER_STATE_DESC_H__
#define __RENDER_STATE_DESC_H__
#include <map>
#include "DrawDrv/RenderState.h"
namespace Shh
{
	class RenderStateDesc
	{
		__Dynamic_Alloc(RenderStateDesc);
	public:
		typedef std::map<uint, DeviceSamplerState> SamplerStateDic;
		enum RenderStateFlag
		{
			eInvalidRenderState = 0,
			eRenderSamplerState = 1,
			eRenderDepthAndStencilState = 2,
			eRenderBlendState = 4,
			eRenderRasterizerState = 8,
			eAllRenderState = (eRenderSamplerState|eRenderDepthAndStencilState|eRenderBlendState|eRenderRasterizerState)
		};
	public:
		RenderStateDesc();
		virtual ~RenderStateDesc();

		void SetSamplerState(const uint& mask, const DeviceSamplerState& state);

		void SetSamplerState(const SamplerStateDic& dic);

		const SamplerStateDic& GetSamplerStateDic() const;

		void SetBlendState(const DeviceBlendState& state);
		const DeviceBlendState& GetBlendState() const;

		void SetRasterizerState(const DeviceRasterizerState& state);
		const DeviceRasterizerState& GetRasterizerState() const;

		void SetDepthAndStencilState(const DeviceDepthAndStencilState& state);
		const DeviceDepthAndStencilState& GetDepthAndStencilState() const;

		void SetUpdateFlag(unsigned int flag);
		unsigned int GetUpdateFlag() const;

	private:
		SamplerStateDic			mSamplerStateDic;//±£¡Ù
		DeviceBlendState		mRenderBlendState;
		DeviceRasterizerState	mRenderRasterizerState;
		DeviceDepthAndStencilState	mRenderDepthStencilState;
		unsigned int			mUpdateFlag;
	};

	inline void
		RenderStateDesc::SetSamplerState(const uint& mask, const DeviceSamplerState& state)
	{
		mSamplerStateDic[mask] = state;
	}

	inline void
		RenderStateDesc::SetSamplerState(const SamplerStateDic& state)
	{
		mSamplerStateDic = state;
	}

	inline const RenderStateDesc::SamplerStateDic& 
		RenderStateDesc::GetSamplerStateDic() const
	{
		return mSamplerStateDic;
	}

	inline void
		RenderStateDesc::SetBlendState(const DeviceBlendState& state)
	{
		mRenderBlendState = state;
		mUpdateFlag |= eRenderBlendState;
	}

	inline const DeviceBlendState&
		RenderStateDesc::GetBlendState() const
	{
		return mRenderBlendState;
	}

	inline void
		RenderStateDesc::SetRasterizerState(const DeviceRasterizerState& state)
	{
		mRenderRasterizerState = state;
		mUpdateFlag |= eRenderRasterizerState;
	}

	inline const DeviceRasterizerState&
		RenderStateDesc::GetRasterizerState() const
	{
		return mRenderRasterizerState;
	}

	inline void
		RenderStateDesc::SetDepthAndStencilState(const DeviceDepthAndStencilState& state)
	{
		mRenderDepthStencilState = state;
		mUpdateFlag |= eRenderDepthAndStencilState;
	}

	inline const DeviceDepthAndStencilState&
		RenderStateDesc::GetDepthAndStencilState() const
	{
		return mRenderDepthStencilState;
	}

	inline void
		RenderStateDesc::SetUpdateFlag(unsigned int flag)
	{
		mUpdateFlag = flag;
	}
	inline unsigned int
		RenderStateDesc::GetUpdateFlag() const
	{
		return mUpdateFlag;
	}
}
#endif
