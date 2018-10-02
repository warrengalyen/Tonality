#ifndef CONTROLTRIGGER_H
#define CONTROLTRIGGER_H

#include "ControlGenerator.h"

namespace Tonality {

	namespace Tonality_ {

		class ControlTrigger_ : public ControlGenerator_ {

		protected:
			void computeOutput(const SynthesisContext_ & context);
			bool doTrigger;

		public:
			ControlTrigger_();
			void trigger(float value);

		};

		inline void ControlTrigger_::computeOutput(const SynthesisContext_ & context) {
			output_.triggered = doTrigger;
			doTrigger = false;
		}

	}

	/*!
	  Status changes to ControlGeneratorStatusHasChanged when trigger is called
	*/


	class ControlTrigger : public TemplatedControlGenerator<Tonality_::ControlTrigger_> {

	public:

		void trigger(float value = 1);

	};
}

#endif