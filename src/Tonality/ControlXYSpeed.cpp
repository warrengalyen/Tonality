#include "ControlXYSpeed.h"

namespace Tonality {
	namespace Tonality_ {

		ControlXYSpeed_::ControlXYSpeed_() : lastYVal(0), lastXVal(0) {

		}

		void  ControlXYSpeed_::setX(ControlGenerator xArg) {
			x = xArg;
		}

		void  ControlXYSpeed_::setY(ControlGenerator yArg) {
			y = yArg;
		}


	} // Namespace Tonality_



} // Namespace Tonality