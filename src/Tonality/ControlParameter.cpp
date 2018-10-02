#include "ControlParameter.h"

namespace Tonality {
	namespace Tonality_ {

		ControlParameter_::ControlParameter_() :
			name_(""),
			displayName_(""),
			min_(0),
			max_(1),
			type_(ControlParameterTypeContinuous),
			isLogarithmic_(false)
		{

		}

		void ControlParameter_::setNormalizedValue(TonalityFloat normVal) {
			if (isLogarithmic_) {
				setValue(mapLinToLog(normVal, min_, max_));
			}
			else {
				setValue(map(normVal, 0.f, 1.f, min_, max_, true));
			}
		}

		TonalityFloat ControlParameter_::getNormalizedValue() {
			if (isLogarithmic_) {
				return mapLogToLin(value_, min_, max_);
			}
			else {
				return map(value_, min_, max_, 0.f, 1.f, true);
			}
		}


	} // Namespace Tonality_


	string ControlParameter::getName() {
		return gen()->getName();
	}

	ControlParameter &  ControlParameter::name(string name) {
		gen()->setName(name);
		return *this;
	}

	string ControlParameter::getDisplayName() {
		return gen()->getDisplayName();
	}

	ControlParameter &  ControlParameter::displayName(string displayName) {
		gen()->setDisplayName(displayName);
		return *this;
	}

	TonalityFloat ControlParameter::getValue() {
		return gen()->getValue();
	}

	ControlParameter &  ControlParameter::value(TonalityFloat value) {
		gen()->setValue(value);
		return *this;
	}

	TonalityFloat ControlParameter::getMin() {
		return gen()->getMin();
	}

	ControlParameter &  ControlParameter::min(TonalityFloat min) {
		gen()->setMin(min);
		return *this;
	}

	ControlParameter &  ControlParameter::max(TonalityFloat max) {
		gen()->setMax(max);
		return *this;
	}

	TonalityFloat ControlParameter::getMax() {
		return gen()->getMax();
	}

	ControlParameter &  ControlParameter::parameterType(ControlParameterType type) {
		gen()->setType(type);
		return *this;
	}

	ControlParameterType  ControlParameter::getParameterType() {
		return gen()->getType();
	}

	ControlParameter &  ControlParameter::logarithmic(bool isLogarithmic) {
		gen()->setIsLogarithmic(isLogarithmic);
		return *this;
	}

	bool ControlParameter::getIsLogarithmic() {
		return gen()->getIsLogarithmic();
	}

	ControlParameter & ControlParameter::setNormalizedValue(TonalityFloat value) {
		gen()->setNormalizedValue(value);
		return *this;
	}

	TonalityFloat ControlParameter::getNormalizedValue() {
		return gen()->getNormalizedValue();
	}

} // Namespace Tonality