#include "ControlDelay.h"

namespace Tonality {

	namespace Tonality_ {

		ControlDelay_::ControlDelay_() :
			readHead_(0),
			writeHead_(0),
			maxDelay_(0)
		{
		}

		void ControlDelay_::initialize(float maxDelayTime) {
			maxDelay_ = max(maxDelayTime * sampleRate() / kSynthesisBlockSize, 1);
			delayLine_.resize(maxDelay_);
			readHead_ = maxDelay_ - 1;
		}

	} // Namespace Tonality_

	ControlDelay::ControlDelay(float maxDelayTime) {
		this->gen()->initialize(maxDelayTime);
	}

} // Namespace Tonality