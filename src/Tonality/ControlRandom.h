#ifndef CONTROLRANDOM_H
#define CONTROLRANDOM_H

#include <iostream>

#include <iostream>
#include "ControlConditioner.h"

namespace Tonality {

	namespace Tonality_ {

		class ControlRandom_ : public ControlGenerator_ {


			void computeOutput(const SynthesisContext_ & context);
		public:

			ControlGenerator max;
			ControlGenerator min;
			ControlGenerator trigger;

			ControlRandom_();

			void setMax(ControlGenerator maxArg) { max = maxArg; };
			void setMin(ControlGenerator minArg) { min = minArg; };
			void setTrigger(ControlGenerator arg) { trigger = arg; }
		};

		inline void ControlRandom_::computeOutput(const SynthesisContext_ & context) {
			ControlGeneratorOutput minOut = min.tick(context);
			ControlGeneratorOutput maxOut = max.tick(context);

			bool outInRange = (output_.value >= minOut.value) && (output_.value <= maxOut.value);

			if (!outInRange || trigger.tick(context).triggered) {
				output_.triggered = true;
				output_.value = randomFloat(minOut.value, maxOut.value);
			}
			else {
				output_.triggered = false;
			}
		}

	}

	/*
	  Outputs a random value when triggered, between in and max.
	*/

	class ControlRandom : public TemplatedControlGenerator<Tonality_::ControlRandom_> {
	public:
			TONALITY_MAKE_CTRL_GEN_SETTERS(ControlRandom, max, setMax)
			TONALITY_MAKE_CTRL_GEN_SETTERS(ControlRandom, min, setMin)
			TONALITY_MAKE_CTRL_GEN_SETTERS(ControlRandom, trigger, setTrigger)
	};

}


#endif