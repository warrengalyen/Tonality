#include "LFNoise.h"

namespace Tonality {

	namespace Tonality_ {


		LFNoise_::LFNoise_() : mCounter(0) {
			mFreqFrames.resize(kSynthesisBlockSize);
		}

		void  LFNoise_::setFreq(ControlGenerator freq) {
			mFreq = freq;
		}


	}

}