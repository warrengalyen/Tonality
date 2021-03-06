#include "CombFilter.h"

namespace Tonality {
	namespace Tonality_ {

		CombFilter_::CombFilter_() {
			delayTimeFrames_.resize(kSynthesisBlockSize, 1, 0);
		}

		void CombFilter_::initialize(float initialDelayTime, float maxDelayTime) {
			if (maxDelayTime < 0) maxDelayTime = initialDelayTime * 1.5;
			delayLine_.initialize(maxDelayTime, 1);
			delayTimeGen_ = FixedValue(initialDelayTime);
		}

		FilteredFBCombFilter6_::FilteredFBCombFilter6_() : lastOutLow_(0), lastOutHigh_(0)
		{
			// don't care about interpolation here, since this is optimized for reverb (faster)
			delayLine_.setInterpolates(false);
		}

	} // Namespace Tonality_

	FFCombFilter::FFCombFilter(float initialDelayTime, float maxDelayTime)
	{
		gen()->initialize(initialDelayTime, maxDelayTime);
		delayTime(initialDelayTime);
		scaleFactor(0.5f);
	}

	FBCombFilter::FBCombFilter(float initialDelayTime, float maxDelayTime)
	{
		gen()->initialize(initialDelayTime, maxDelayTime);
		delayTime(initialDelayTime);
		scaleFactor(0.5f);
	}

	FilteredFBCombFilter6::FilteredFBCombFilter6(float initialDelayTime, float maxDelayTime)
	{
		gen()->initialize(initialDelayTime, maxDelayTime);
		delayTime(initialDelayTime);
		scaleFactor(0.5f);
		lowpassCutoff(12000.0f);
		highpassCutoff(20.0f);
	}


} // Namespace Tonality