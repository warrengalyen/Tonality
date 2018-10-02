#ifndef RAMPEDVALUE_H
#define RAMPEDVALUE_H

#include <iostream>
#include "Generator.h"
#include "ControlValue.h"

namespace Tonality {

	namespace Tonality_ {

		class RampedValue_ : public Generator_ {

		protected:

			bool finished_;
			unsigned long count_;
			unsigned long len_;
			TonalityFloat target_;
			TonalityFloat last_;
			TonalityFloat inc_;
			ControlGenerator targetGen_;
			ControlGenerator lengthGen_;
			ControlGenerator valueGen_;

			void computeSynthesisBlock(const SynthesisContext_ & context);

		public:
			RampedValue_();
			~RampedValue_();

			void setValueGen(ControlGenerator value);
			void setTargetGen(ControlGenerator target);
			void setLengthGen(ControlGenerator length);

			// internal state setters
			void updateValue(TonalityFloat value);
			void updateTarget(TonalityFloat target, unsigned long lengthSamp);
			bool isFinished();

		};

		inline void RampedValue_::computeSynthesisBlock(const SynthesisContext_ & context) {

			// First set the value, if necessary (abort ramp, go immediately to value)
			ControlGeneratorOutput valueOutput = valueGen_.tick(context);
			if (valueOutput.triggered) {
				updateValue(valueOutput.value);
			}

			// Then update the target or ramp length (start a new ramp)
			ControlGeneratorOutput lengthOutput = lengthGen_.tick(context);
			ControlGeneratorOutput targetOutput = targetGen_.tick(context);
			if (lengthOutput.triggered || targetOutput.triggered) {
				unsigned long lSamp = lengthOutput.value*Tonality::sampleRate();
				updateTarget(targetOutput.value, lSamp);
			}

			TonalityFloat *fdata = &outputFrames_[0];
			unsigned int nFrames = kSynthesisBlockSize;
			unsigned int stride = outputFrames_.channels();

			// edge case
			if (count_ == len_) {
				finished_ = true;
			}

			if (finished_) {
#ifdef USE_APPLE_ACCELERATE
				vDSP_vfill(&last_, fdata, stride, nFrames);
#else
				for (unsigned int i = 0; i < nFrames; i++) {
					*fdata = last_;
					fdata += stride;
				}
#endif
			}
			else {

				// figure out if we will finish the ramp in this tick
				unsigned long remainder = count_ > len_ ? 0 : len_ - count_;

				if (remainder < nFrames) {

					// fill part of the ramp - no need to check if remainder is 1 when using vramp
					// uses algorithm out[n] = start + n * increment;
#ifdef USE_APPLE_ACCELERATE
// starting point
					last_ += inc_;
					vDSP_vramp(&last_, &inc_, fdata, stride, remainder);

#ifdef TONALITY_DEBUG
					if (*fdata != *fdata) {
						Tonality::error("RampedValue_::computeSynthesisBlock NaN detected.\n");
					}
#endif

#else
					for (unsigned int i = 0; i < remainder; i++) {
						last_ += inc_;
						*fdata = last_;
						fdata += stride;
					}
#endif

#ifdef USE_APPLE_ACCELERATE
					vDSP_vfill(&target_, fdata + remainder, stride, nFrames - remainder);
#else
					for (unsigned int i = remainder; i < nFrames; i++) {
						*fdata = target_;
						fdata += stride;
					}
#endif

					count_ = len_;
					last_ = target_;
					finished_ = true;
				}
				else {

					// fill the whole ramp
#ifdef USE_APPLE_ACCELERATE
					last_ += inc_;
					vDSP_vramp(&last_, &inc_, fdata, stride, nFrames);

#ifdef TONALITY_DEBUG
					if (*fdata != *fdata) {
						Tonality::error("RampedValue_::computeSynthesisBlock NaN detected.\n");
					}
#endif

#else
					for (unsigned int i = 0; i < nFrames; i++) {
						last_ += inc_;
						*fdata = last_;
						fdata += stride;
					}
#endif

					count_ += nFrames;
					last_ = outputFrames_(nFrames - 1, 0);
				}
			}

#ifdef TONALITY_DEBUG
			if (*fdata != *fdata) {
				Tonality::error("RampedValue_::computeSynthesisBlock NaN detected.\n");
			}
#endif

			// mono source, so need to fill out channels if necessary
			outputFrames_.fillChannels();

		}

#pragma mark - Generator setters

		inline void RampedValue_::setValueGen(ControlGenerator value) {
			valueGen_ = value;
		}

		inline void RampedValue_::setTargetGen(ControlGenerator target) {
			targetGen_ = target;
		}

		inline void RampedValue_::setLengthGen(ControlGenerator length) {
			lengthGen_ = length;
		}

#pragma mark - Internal State setters

		inline void RampedValue_::updateValue(TonalityFloat value) {

			// When the value gen changes, immediately abort the current ramp and go to the new value.

			finished_ = true;
			last_ = value;
			target_ = value;
			inc_ = 0;
			count_ = 0;
		}

		inline void RampedValue_::updateTarget(TonalityFloat target, unsigned long lengthSamp) {

			target_ = target;
			count_ = 0;

			// ND- Fixes bug with NaN when using Accelerate ramps
			if (lengthSamp == 0 || target_ == last_) {
				last_ = target_;
				finished_ = true;
				inc_ = 0;
			}
			else {
				len_ = lengthSamp;
				inc_ = (TonalityFloat)(target_ - last_) / len_;
				finished_ = false;
			}

#ifdef TONALITY_DEBUG
			if (inc_ != inc_) {
				Tonality::error("RampedValue_::updateTarget NaN found\n");
			}
#endif


		}
	}

	class RampedValue : public TemplatedGenerator<Tonality_::RampedValue_> {

	public:

		RampedValue(TonalityFloat startValue = 0, TonalityFloat initLength = 0.05) {
			target(startValue);
			value(startValue);
			length(initLength);
		}

		//! Set target value
		/*!
			Changes to target gen input will create a new ramp from current value to target over the current length
		*/
		TONALITY_MAKE_CTRL_GEN_SETTERS(RampedValue, target, setTargetGen);

		//! Set length before reaching target value, in ms
		/*!
			Changes to length gen input will create a new ramp from current value to target over the provided length
		*/
		TONALITY_MAKE_CTRL_GEN_SETTERS(RampedValue, length, setLengthGen);

		//! Go to value immediately
		/*!
			Changes to the value gen input will abort the current ramp and go immediately to the specified value.
			Output will remain steady until a new target or length is set.
		*/
		TONALITY_MAKE_CTRL_GEN_SETTERS(RampedValue, value, setValueGen);

		bool isFinished();

	};
}

#endif