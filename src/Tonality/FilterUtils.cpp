#include "FilterUtils.h"

namespace Tonality {

	Biquad::Biquad() {
		memset(coef_, 0, 5 * sizeof(TonalityFloat));
		inputVec_.resize(kSynthesisBlockSize + 4, 1, 0);
		outputVec_.resize(kSynthesisBlockSize + 4, 1, 0);
	}

}