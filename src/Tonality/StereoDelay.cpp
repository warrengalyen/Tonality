#include "StereoDelay.h"

namespace Tonality {
	namespace Tonality_ {

		StereoDelay_::StereoDelay_() {
			setIsStereoOutput(true);
			setIsStereoInput(true);
			delayTimeFrames_[TONALITY_LEFT].resize(kSynthesisBlockSize, 1, 0);
			delayTimeFrames_[TONALITY_RIGHT].resize(kSynthesisBlockSize, 1, 0);
			fbkFrames_.resize(kSynthesisBlockSize, 1, 0);

			setFeedback(FixedValue(0.0));
			setDryLevelGen(FixedValue(0.5));
			setWetLevelGen(FixedValue(0.5));
		}

		void StereoDelay_::initialize(float leftDelayArg, float rightDelayArg, float maxDelayLeft, float maxDelayRight) {

			if (maxDelayLeft <= 0) maxDelayLeft = leftDelayArg * 1.5;
			if (maxDelayRight <= 0) maxDelayRight = rightDelayArg * 1.5;
			delayLine_[TONALITY_LEFT].initialize(maxDelayLeft, 1);
			delayLine_[TONALITY_RIGHT].initialize(maxDelayRight, 1);
		}


	} // Namespace Tonality_

	StereoDelay::StereoDelay(float leftDelay, float rightDelay, float maxDelayLeft, float maxDelayRight) {
		gen()->initialize(leftDelay, rightDelay, maxDelayLeft, maxDelayRight);
		delayTimeLeft(leftDelay);
		delayTimeRight(rightDelay);
	}

} // Namespace Tonality