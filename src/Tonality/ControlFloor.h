#ifndef CONTROLFLOOR_H
#define CONTROLFLOOR_H

#include "ControlConditioner.h"

namespace Tonality {

	namespace Tonality_ {

		class ControlFloor_ : public ControlConditioner_ {

			inline void computeOutput(const SynthesisContext_ & context) {
				output_.value = (int)input_.tick(context).value;
				output_.triggered = input_.tick(context).triggered;
			}

		};

	}

	class ControlFloor : public TemplatedControlConditioner<ControlFloor, Tonality_::ControlFloor_> {};

}

#endif