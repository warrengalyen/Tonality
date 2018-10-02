#include "ControlCallback.h"
#if TONALITY_HAS_CPP_11

namespace Tonality {
	namespace Tonality_ {

		void ControlCallback_::computeOutput(const SynthesisContext_ & context) {
			ControlGeneratorOutput inputOut = input_.tick(context);
			if (inputOut.triggered) {
				callback_(inputOut);
			}
		}

		void  ControlCallback_::setCallback(function<void(ControlGeneratorOutput)> fn) {
			callback_ = fn;
		}

	} // Namespace Tonality_

	ControlCallback::ControlCallback(Synth* synth, function<void(ControlGeneratorOutput)> fn) {
		synth->addAuxControlGenerator(*this);
		gen()->setCallback(fn);
	}


} // Namespace Tonality

#endif