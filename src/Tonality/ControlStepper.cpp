#include "ControlStepper.h"

namespace Tonality {
	namespace Tonality_ {

		ControlStepper_::ControlStepper_() :hasBeenTriggered(false) {
			start = ControlValue(0);
			end = ControlValue(1);
			step = ControlValue(1);
			direction = 1;
			bidirectional = ControlValue(0);
		}

	} // Namespace Tonality_



} // Namespace Tonality