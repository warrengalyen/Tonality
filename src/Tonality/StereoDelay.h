#ifndef STEREODELAY_H
#define STEREODELAY_H

#include "Effect.h"
#include "DelayUtils.h"

namespace Tonality {

	namespace Tonality_ {

		class StereoDelay_ : public WetDryEffect_ {

		protected:

			Generator delayTimeGen_[2];
			TonalityFrames delayTimeFrames_[2];

			Generator fbkGen_;
			TonalityFrames fbkFrames_;

			DelayLine delayLine_[2];

			void computeSynthesisBlock(const SynthesisContext_ &context);

		public:

			StereoDelay_();

			void initialize(float leftDelayArg, float rightDelayArg, float maxDelayLeft, float maxDelayRight);

			void setFeedback(Generator arg) {
				fbkGen_ = arg;
			};

			void setDelayTimeLeft(Generator arg) {
				delayTimeGen_[0] = arg;
			};

			void setDelayTimeRight(Generator arg) {
				delayTimeGen_[1] = arg;
			};


		};

		inline void StereoDelay_::computeSynthesisBlock(const SynthesisContext_ &context) {

			delayTimeGen_[0].tick(delayTimeFrames_[TONALITY_LEFT], context);
			delayTimeGen_[1].tick(delayTimeFrames_[TONALITY_RIGHT], context);
			fbkGen_.tick(fbkFrames_, context);

			TonalityFloat outSamp[2], fbk;
			TonalityFloat *dryptr = &dryFrames_[0];
			TonalityFloat *outptr = &outputFrames_[0];
			TonalityFloat *fbkptr = &fbkFrames_[0];
			TonalityFloat *delptr_l = &(delayTimeFrames_[TONALITY_LEFT])[0];
			TonalityFloat *delptr_r = &(delayTimeFrames_[TONALITY_RIGHT])[0];

			for (unsigned int i = 0; i < kSynthesisBlockSize; i++) {

				// Don't clamp feeback - be careful! Negative feedback could be interesting.
				fbk = *fbkptr++;

				outSamp[TONALITY_LEFT] = delayLine_[TONALITY_LEFT].tickOut(*delptr_l++);
				outSamp[TONALITY_RIGHT] = delayLine_[TONALITY_RIGHT].tickOut(*delptr_r++);

				// output left sample
				*outptr++ = outSamp[TONALITY_LEFT];
				delayLine_[TONALITY_LEFT].tickIn(*dryptr++ + outSamp[TONALITY_LEFT] * fbk);

				// output right sample
				*outptr++ = outSamp[TONALITY_RIGHT];
				delayLine_[TONALITY_RIGHT].tickIn(*dryptr++ + outSamp[TONALITY_RIGHT] * fbk);

				// advance delay lines
				delayLine_[TONALITY_LEFT].advance();
				delayLine_[TONALITY_RIGHT].advance();
			}
		}

	}

	class StereoDelay : public TemplatedWetDryEffect<StereoDelay, Tonality_::StereoDelay_> {

	public:

		StereoDelay(float leftDelay, float rightDelay, float maxDelayLeft = -1, float maxDelayRight = -1);

		TONALITY_MAKE_GEN_SETTERS(StereoDelay, feedback, setFeedback)
		TONALITY_MAKE_GEN_SETTERS(StereoDelay, delayTimeLeft, setDelayTimeLeft)
		TONALITY_MAKE_GEN_SETTERS(StereoDelay, delayTimeRight, setDelayTimeRight)

	};
}

#endif