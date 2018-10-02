#include "ControlRecorder.h"

namespace Tonality {
	namespace Tonality_ {

		ControlRecorder_::ControlRecorder_() : playbackHead(recording.begin()) {}

		void  ControlRecorder_::setMode(ControlGenerator modeArg) {
			mode = modeArg;
		}

	} // Namespace Tonality_

} // Namespace Tonality