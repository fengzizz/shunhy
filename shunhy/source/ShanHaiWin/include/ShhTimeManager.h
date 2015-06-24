#pragma once
#include <ctime>

namespace Shh{
	class ShhTimeManager //: public ITimeManager
	{
	public:
		virtual void SetTimeScale(float scale);
		virtual float GetTimeScale();
		void Start();
		//void Stop();
		void Pause();
		void Continue();
		void Tick();
		virtual ~ShhTimeManager();
		ShhTimeManager();
	private:
		clock_t mTotalTime;
		clock_t mGameTime;
		float mScale;
	};
}