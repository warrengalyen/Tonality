#include "MonoToStereoPanner.h"

namespace Tonality {

	namespace Tonality_ {

		MonoToStereoPanner_::MonoToStereoPanner_() {
			setIsStereoOutput(true);
			panFrames.resize(kSynthesisBlockSize, 1);
			setPan(ControlValue(0));
		}
		MonoToStereoPanner_::~MonoToStereoPanner_() {}

		void MonoToStereoPanner_::setPan(ControlGenerator panArg) {
			panControlGen = panArg;
		}
	}

}