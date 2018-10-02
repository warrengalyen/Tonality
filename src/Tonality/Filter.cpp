#include "Filters.h"

namespace Tonality {
	namespace Tonality_ {

		// ================================
		//       Filter Base Class
		// ================================

		Filter_::Filter_() :
			cutoff_(FixedValue(20000)),
			Q_(FixedValue(0.7071)),
			bypass_(ControlValue(0)),
			bNormalizeGain_(true)
		{
			workspace_.resize(kSynthesisBlockSize, 1, 0);
		}

		void Filter_::setInput(Generator input) {
			Effect_::setInput(input);
			setIsStereoInput(input.isStereoOutput());
			setIsStereoOutput(input.isStereoOutput());
		}

	} // Namespace Tonality_



} // Namespace Tonality