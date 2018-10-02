#include "ControlArithmetic.h"

namespace Tonality {
	namespace Tonality_ {

		void ControlAdder_::input(ControlGenerator input) {
			inputs.push_back(input);
		}

		void ControlMultiplier_::input(ControlGenerator input) {
			inputs.push_back(input);
		}

	} // Namespace Tonality_

} // Namespace Tonality