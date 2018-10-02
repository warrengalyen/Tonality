#include "RectWave.h"

namespace Tonality {
	namespace Tonality_ {

		RectWave_::RectWave_() : phaseAccum_(0) {
			pwmGen_ = FixedValue(0.5);
			freqFrames_.resize(kSynthesisBlockSize, 1, 0);
			pwmFrames_.resize(kSynthesisBlockSize, 1, 0);
		}

		// ------

		RectWaveBL_::RectWaveBL_()
		{
			pwmGen_ = FixedValue(0.5);
			pwmFrames_.resize(kSynthesisBlockSize, 1, 0);
		}

	} // Namespace Tonality_



} // Namespace Tonality