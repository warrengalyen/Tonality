#ifndef CONTROLCALLBACK_H
#define CONTROLCALLBACK_H

#include "ControlConditioner.h"

#if TONALITY_HAS_CPP_11
#include <functional>
#include "Synth.h"

namespace Tonality {

	namespace Tonality_ {

		class ControlCallback_ : public ControlConditioner_ {

		protected:
			void computeOutput(const SynthesisContext_ & context);
			function<void(ControlGeneratorOutput)> callback_;

		public:
			void setCallback(function<void(ControlGeneratorOutput)> fn);

		};

	}

	/*!
	  Pass a lambda function to a controlgenerator. That function will be called when the input ControlGenerator sends a "triggered" message. Constructor takes two arguments -- the synth that owns the ControlCallback, and a lambda function
	*/

	class ControlCallback : public TemplatedControlConditioner<ControlCallback, Tonality_::ControlCallback_> {

	public:

		ControlCallback(Synth* synth, function<void(ControlGeneratorOutput)>);


	};
}

#endif

#endif