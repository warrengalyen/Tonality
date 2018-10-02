#include "Generator.h"

namespace Tonality {
	namespace Tonality_ {

		Generator_::Generator_() : lastFrameIndex_(0), isStereoOutput_(false) {
			outputFrames_.resize(kSynthesisBlockSize, 1, 0);
		}

		Generator_::~Generator_() {}

		void Generator_::setIsStereoOutput(bool stereo) {
			if (stereo != isStereoOutput_) {
				outputFrames_.resize(kSynthesisBlockSize, stereo ? 2 : 1, 0);
			}
			isStereoOutput_ = stereo;
		}

	}
}