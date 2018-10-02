#include "ControlGenerator.h"
#include "RampedValue.h"
#include <cmath>

namespace Tonality {
	namespace Tonality_ {

		ControlGenerator_::ControlGenerator_() :
			lastFrameIndex_(0)
		{
		}

		ControlGenerator_::~ControlGenerator_()
		{
		}

		ControlGeneratorOutput ControlGenerator_::initialOutput() {
			// return output from passing in dummy context
			return tick(Tonality::DummyContext);
		}

	}
	RampedValue ControlGenerator::smoothed(float length) {
		return RampedValue(obj->initialOutput().value, length).target(*this);
	}

}