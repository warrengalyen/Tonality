#ifndef CONTROLCOUNTER_H
#define CONTROLCOUNTER_H

#include "ControlGenerator.h"

namespace Tonality {

	namespace Tonality_ {

		class ControlCounter_ : public ControlGenerator_ {

		protected:
			void computeOutput(const SynthesisContext_ & context);
			ControlGenerator trigger;
			ControlGenerator end;

		public:

			ControlCounter_();

			void setTrigger(ControlGenerator gen) { trigger = gen; };
			void setEnd(ControlGenerator gen) { end = gen; };

		};

		inline void ControlCounter_::computeOutput(const SynthesisContext_ & context) {
			ControlGeneratorOutput tickOut = trigger.tick(context);
			ControlGeneratorOutput endOut = end.tick(context);
			output_.triggered = tickOut.triggered;
			if (tickOut.triggered) {
				output_.value += 1;
				if (output_.value > endOut.value) {
					output_.value = 0;
				}
			}
		}

	}

	class ControlCounter : public TemplatedControlGenerator<Tonality_::ControlCounter_> {

	public:

		TONALITY_MAKE_CTRL_GEN_SETTERS(ControlCounter, trigger, setTrigger);
		TONALITY_MAKE_CTRL_GEN_SETTERS(ControlCounter, end, setEnd);

	};
}

#endif