#include "ControlMetroDivider.h"

namespace Tonality {
	namespace Tonality_ {

		ControlMetroDivider_::ControlMetroDivider_() : tickCounter_(0) {
			divisonsGen_ = ControlValue(1);
			offsetGen_ = ControlValue(0);
			output_.value = 1.f;
		}


	} // Namespace Tonality_



} // Namespace Tonality