#include "RampedValue.h"

namespace Tonality {
	namespace Tonality_ {

		RampedValue_::RampedValue_() :
			finished_(true),
			count_(0),
			len_(0),
			target_(0),
			last_(0),
			inc_(0)
		{
		}

		RampedValue_::~RampedValue_() {

		}


		bool RampedValue_::isFinished() {
			return finished_;
		}

	} // Namespace Tonality_


	bool RampedValue::isFinished() {
		return gen()->isFinished();
	}

} // Namespace Tonality