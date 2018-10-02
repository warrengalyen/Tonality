#ifndef CONTROLMIDITOFREQ_H
#define CONTROLMIDITOFREQ_H

#include <iostream>
#include "ControlConditioner.h"

namespace Tonality {

	namespace Tonality_ {

		class ControlMidiToFreq_ : public ControlConditioner_ {

			void computeOutput(const SynthesisContext_ & context) {
				ControlGeneratorOutput inputOut = input_.tick(context);
				output_.triggered = inputOut.triggered;
				output_.value = mtof(inputOut.value);
			}

		};

	}

	class ControlMidiToFreq : public TemplatedControlConditioner<ControlMidiToFreq, Tonality_::ControlMidiToFreq_> {};

}


#endif