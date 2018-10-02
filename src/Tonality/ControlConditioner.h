#ifndef CONTROLCONDITIONER_H
#define CONTROLCONDITIONER_H


#include <vector>
#include "ControlGenerator.h"
#include "ControlValue.h"

using std::vector;

namespace Tonality {

	namespace Tonality_ {

		class ControlConditioner_ : public ControlGenerator_ {

		protected:

			ControlGenerator input_;

		public:

			void input(ControlGenerator input);

		};

	}

	// The Tonality:: component of the controlconditioner (the smart pointer wrapper) must subclass the
	// following template, in the form <class Wrapper, class PrivateControlGenerator>

	template<class ControlConditionerType, class ControlConditionerType_>
	class TemplatedControlConditioner : public TemplatedControlGenerator<ControlConditionerType_> {

	public:

		ControlConditionerType input(ControlGenerator input) {
			// why doesn't this compile without 'this' ?
			this->gen()->input(input);
			return static_cast<ControlConditionerType&>(*this);
		}

		ControlConditionerType input(float inputVal) {
			return input(ControlValue(inputVal));
		}

	};

	// signal flow operator - sets lhs as input to rhs
	template<class ControlConditionerType, class ControlConditionerType_>
	static ControlConditionerType operator >> (ControlGenerator lhs, TemplatedControlConditioner<ControlConditionerType, ControlConditionerType_> rhs) {
		return rhs.input(lhs);
	}

}

#endif 