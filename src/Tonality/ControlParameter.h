#ifndef CONTROLPARAMETER_H
#define CONTROLPARAMETER_H

#include "ControlValue.h"

namespace Tonality {

	typedef enum {

		ControlParameterTypeContinuous = 0,
		ControlParameterTypeToggle,
		ControlParameterTypeMomentary

	} ControlParameterType;

	namespace Tonality_ {


		// Parameter for controlling a Synth instance
		/*
			ControlParameter acts like a ControlValue but provides an interface for exposing itself to
			a synth, including min, max, type, etc
		 */
		class ControlParameter_ : public ControlValue_ {

		protected:

			string                name_;
			string                displayName_;
			TonalityFloat            min_;
			TonalityFloat            max_;
			ControlParameterType  type_;

			bool                isLogarithmic_;

		public:

			ControlParameter_();

			void        setName(string name) { name_ = name; };
			string      getName() { return name_; };

			void        setDisplayName(string displayName) { displayName_ = displayName; };
			string      getDisplayName() { return displayName_; };

			void        setMin(TonalityFloat min) { min_ = min; };
			TonalityFloat  getMin() { return min_; };

			void        setMax(TonalityFloat max) { max_ = max; };
			TonalityFloat  getMax() { return max_; };

			void                  setType(ControlParameterType type) { type_ = type; };
			ControlParameterType  getType() { return type_; };

			void        setIsLogarithmic(bool isLogarithmic) { isLogarithmic_ = isLogarithmic; };
			bool        getIsLogarithmic() { return isLogarithmic_; };

			void        setNormalizedValue(TonalityFloat normVal);
			TonalityFloat  getNormalizedValue();

		};

	}

	class ControlParameter : public TemplatedControlGenerator<Tonality_::ControlParameter_> {

	public:

		string              getName();
		ControlParameter &  name(string name);

		string              getDisplayName();
		ControlParameter &  displayName(string displayName);

		TonalityFloat          getValue();
		ControlParameter &  value(TonalityFloat value);

		TonalityFloat          getMin();
		ControlParameter &  min(TonalityFloat min);

		TonalityFloat          getMax();
		ControlParameter &  max(TonalityFloat max);

		ControlParameterType  getParameterType();
		ControlParameter &    parameterType(ControlParameterType type);

		bool                getIsLogarithmic();
		ControlParameter &  logarithmic(bool isLogarithmic);

		// Convenience methods for setting/getting value normalized linearly 0-1,
		// mapped to min/max range, with log applied if necessary
		TonalityFloat       getNormalizedValue();
		ControlParameter &  setNormalizedValue(TonalityFloat value);
	};
}

#endif