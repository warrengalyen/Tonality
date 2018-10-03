#include "SawtoothWave.h"

namespace Tonality {
	namespace Tonality_ {

		AngularWave_::AngularWave_() : phaseAccum_(0) {

			freqFrames_.resize(kSynthesisBlockSize, 1, 0);
			slopeFrames_.resize(kSynthesisBlockSize, 1, 0);

			slopeGen_ = FixedValue(0);
			freqGen_ = FixedValue(440);

		}


	} // Namespace Tonality_



} // Namespace Tonality