#ifndef CONTROLMETRO_H
#define CONTROLMETRO_H

#include "ControlGenerator.h"

namespace Tonality {

	namespace Tonality_ {

		class ControlMetro_ : public ControlGenerator_ {

		protected:

			double lastClickTime_;

			ControlGenerator bpm_;

			void computeOutput(const SynthesisContext_ & context);

		public:

			ControlMetro_();

			void setBPMGen(ControlGenerator bpmGen) { bpm_ = bpmGen; };

		};

		inline void ControlMetro_::computeOutput(const SynthesisContext_ & context) {

			double sPerBeat = 60.0 / max(0.001, bpm_.tick(context).value);
			double delta = context.elapsedTime - lastClickTime_;
			if (delta >= 2 * sPerBeat || delta < 0 || lastClickTime_ == 0.0) {
				// account for bpm interval outrunning tick interval or timer wrap-around
				lastClickTime_ = context.elapsedTime;
				output_.triggered = true;
			}
			else if (delta >= sPerBeat) {
				// acocunt for drift
				lastClickTime_ += sPerBeat;
				output_.triggered = true;
			}
			else {
				output_.triggered = false;
			}

			output_.value = 1;

		}

	}

	//!Ouputs a "changed" status at a regular BPM interval
	class ControlMetro : public TemplatedControlGenerator<Tonality_::ControlMetro_> {

	public:

		ControlMetro(float bpm = 120) {
			gen()->setBPMGen(ControlValue(bpm));
		}

		ControlMetro(ControlGenerator bpm) {
			gen()->setBPMGen(bpm);
		}

		TONALITY_MAKE_CTRL_GEN_SETTERS(ControlMetro, bpm, setBPMGen);
	};
}

#endif