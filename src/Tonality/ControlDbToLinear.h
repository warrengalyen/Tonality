#ifndef CONTROLDBTOLINEAR_H
#define CONTROLDBTOLINEAR_H

#include "ControlConditioner.h"

namespace Tonality {

	namespace Tonality_ {

		class ControlDbToLinear_ : public ControlConditioner_ {

		protected:

			void computeOutput(const SynthesisContext_ & context);

		};

		inline void ControlDbToLinear_::computeOutput(const SynthesisContext_ & context) {

			ControlGeneratorOutput inputOutput = input_.tick(context);
			output_.triggered = inputOutput.triggered;
			if (inputOutput.triggered) {
				output_.value = dBToLin(inputOutput.value);
			}

		}

	}

	class ControlDbToLinear : public TemplatedControlConditioner<ControlDbToLinear, Tonality_::ControlDbToLinear_> {

	public:

	};
}

#endif
