#ifndef CONTROLMETRODIVIDER_H
#define CONTROLMETRODIVIDER_H

#include "ControlConditioner.h"

namespace Tonality {

	namespace Tonality_ {

		class ControlMetroDivider_ : public ControlConditioner_ {

		protected:

			void computeOutput(const SynthesisContext_ & context);

			ControlGenerator divisonsGen_;
			ControlGenerator offsetGen_;

			unsigned int offset_;
			unsigned int tickCounter_;

		public:

			ControlMetroDivider_();

			void setDivisionsGen(ControlGenerator gen) { divisonsGen_ = gen; }
			void setOffsetGen(ControlGenerator gen) { offsetGen_ = gen; }

		};

		inline   void ControlMetroDivider_::computeOutput(const SynthesisContext_ & context) {

			offset_ = (unsigned int)(offsetGen_.tick(context).value);
			unsigned int divisions = max(1, divisonsGen_.tick(context).value);

			output_.triggered = false;

			if (input_.tick(context).triggered)
			{
				unsigned int modcount = (tickCounter_++ + offset_) % divisions;
				if (modcount == 0) {
					output_.triggered = true;
				}

				if (tickCounter_ >= divisions) tickCounter_ = 0;
			}

		}

	}

	class ControlMetroDivider : public TemplatedControlConditioner<ControlMetroDivider, Tonality_::ControlMetroDivider_>
	{
	public:

		TONALITY_MAKE_CTRL_GEN_SETTERS(ControlMetroDivider, divisions, setDivisionsGen);
		TONALITY_MAKE_CTRL_GEN_SETTERS(ControlMetroDivider, offset, setOffsetGen);

	};
}

#endif