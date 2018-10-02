#ifndef CONTROLVALUE_H
#define CONTROLVALUE_H

#include "ControlGenerator.h"

namespace Tonality {

	namespace Tonality_ {

		class ControlValue_ : public ControlGenerator_ {

		public:

			ControlValue_();

			inline void setValue(float value) {
				value_ = value;
				changed_ = true;
			}

			// Get current value directly
			TonalityFloat getValue() { return value_; };

		protected:

			void computeOutput(const SynthesisContext_ & context);

			TonalityFloat	value_;
			bool			changed_;

		};

		inline void ControlValue_::computeOutput(const SynthesisContext_ & context) {
			output_.triggered = (changed_ || context.forceNewOutput);
			changed_ = context.forceNewOutput; // if new output forced, don't reset changed status until next tick
			output_.value = value_;
		}
	}

	class ControlValue : public TemplatedControlGenerator<Tonality_::ControlValue_> {

	public:

		ControlValue(TonalityFloat value = 0) {
			gen()->setValue(value);
		}

		ControlValue & value(TonalityFloat value)
		{
			gen()->setValue(value);
			return *this;
		}

		// for higher-level access - doesn't affect tick state
		float getValue() {
			return gen()->getValue();
		}

	};
}

#endif