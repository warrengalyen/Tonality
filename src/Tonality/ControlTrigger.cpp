#include "ControlTrigger.h"

namespace Tonality {
	namespace Tonality_ {

		ControlTrigger_::ControlTrigger_() : doTrigger(false) {

		}

		void ControlTrigger_::trigger(float value) {
			doTrigger = true;
			output_.value = value;
		}

	} // Namespace Tonality_


	void  ControlTrigger::trigger(float value) {
		gen()->trigger(value);
	}

} // Namespace Tonality