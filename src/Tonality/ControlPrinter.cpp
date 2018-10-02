#include "ControlPrinter.h"

namespace Tonality {
	namespace Tonality_ {

		ControlPrinter_::ControlPrinter_()
			:message("%f\n"), hasPrinted(false) {

		}

		void ControlPrinter_::setMessage(string messageArg) {
			message = "Tonality::ControlPrinter message:" + messageArg + "\n";
		}

	} // Namespace Tonality_



} // Namespace Tonality