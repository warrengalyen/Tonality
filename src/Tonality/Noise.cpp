#include "Noise.h"

namespace Tonality {
	namespace Tonality_ {

		PinkNoise_::PinkNoise_() : pinkCount_(1), pinkAccum_(0) {
			memset(pinkBins_, 0, kNumPinkNoiseBins * sizeof(TonalityFloat));
		}

	}
}