#ifndef FIXEDVALUE_H
#define FIXEDVALUE_H

#include "ControlValue.h"
#include "Generator.h"

namespace Tonality {

	namespace Tonality_ {

		class FixedValue_ : public Generator_ {

		protected:

			ControlGenerator valueGen;

			void computeSynthesisBlock(const SynthesisContext_ & context);


		public:

			FixedValue_(float TonalityFloat = 0);

			void setValue(ControlGenerator val) {
				valueGen = val;
			}

		};

		inline void FixedValue_::computeSynthesisBlock(const SynthesisContext_ & context) {

			float* buffStart = &outputFrames_[0];

			ControlGeneratorOutput valueOutput = valueGen.tick(context);

			if (valueOutput.triggered) {

#ifdef USE_APPLE_ACCELERATE

				vDSP_vfill(&valueOutput.value, buffStart, 1, outputFrames_.size());

#else

				std::fill(buffStart, buffStart + outputFrames_.size(), valueOutput.value);

#endif
			}
		}

	}

	class FixedValue : public TemplatedGenerator<Tonality_::FixedValue_> {
	public:
		FixedValue() {}
		FixedValue(float val) {
			setValue(val);
		}
		FixedValue& setValue(float val) {
			gen()->setValue(ControlValue(val));
			return *this;
		}
		FixedValue& setValue(ControlGenerator val) {
			gen()->setValue(val);
			return *this;
		}
	};

}

#endif
