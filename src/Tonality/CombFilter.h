#ifndef COMBFILTER_H
#define COMBFILTER_H

#include "Effect.h"
#include "DelayUtils.h"
#include "FilterUtils.h"

namespace Tonality {

	namespace Tonality_ {

		// Abstract comb-filter gen_ base class
		class CombFilter_ : public Effect_ {

		protected:

			DelayLine           delayLine_;
			Generator           delayTimeGen_;
			ControlGenerator    scaleFactorCtrlGen_;

			TonalityFrames         delayTimeFrames_;

		public:

			CombFilter_();

			void initialize(float initialDelayTime, float maxDelayTime);

			void setDelayTimeGen(Generator gen) { delayTimeGen_ = gen; };

			void setScaleFactorGen(ControlGenerator gen) { scaleFactorCtrlGen_ = gen; };

		};

		// Basic mono feed-forward comb filter
		class FFCombFilter_ : public CombFilter_ {

		protected:

			inline void computeSynthesisBlock(const SynthesisContext_ &context) {

				// tick modulations
				delayTimeGen_.tick(delayTimeFrames_, context);

				TonalityFloat * inptr = &dryFrames_[0];
				TonalityFloat * outptr = &outputFrames_[0];
				TonalityFloat * dtptr = &delayTimeFrames_[0];
				TonalityFloat sf = scaleFactorCtrlGen_.tick(context).value;
				TonalityFloat norm = (1.0f / (1.0f + sf));

				for (unsigned int i = 0; i < kSynthesisBlockSize; i++) {
					delayLine_.tickIn(*inptr);
					*outptr++ = (*inptr++ + delayLine_.tickOut(*dtptr++) * sf) * norm;
					delayLine_.advance();
				}
			}


		};

		// Basic mono feedback comb filter with hook for aditional processing pre-feedback
		class FBCombFilter_ : public CombFilter_ {

		protected:

			inline void computeSynthesisBlock(const SynthesisContext_ &context) {

				// tick modulations
				delayTimeGen_.tick(delayTimeFrames_, context);

				TonalityFloat y = 0;
				TonalityFloat * inptr = &dryFrames_[0];
				TonalityFloat * outptr = &outputFrames_[0];
				TonalityFloat * dtptr = &delayTimeFrames_[0];
				TonalityFloat sf = scaleFactorCtrlGen_.tick(context).value;
				TonalityFloat norm = (1.0f / (1.0f + sf));

				for (unsigned int i = 0; i < kSynthesisBlockSize; i++) {
					y = ((delayLine_.tickOut(*dtptr++) * sf) + *inptr++) * norm;
					delayLine_.tickIn(y);
					*outptr++ = y;
					delayLine_.advance();
				}

			}

		};


		// ------------------------

		// Feedback comb filter with 6dB/oct (one-pole) lpf and hpf, optimized for reverb
		class FilteredFBCombFilter6_ : public CombFilter_ {

		protected:

			TonalityFloat lastOutLow_;
			TonalityFloat lastOutHigh_;

			ControlGenerator lowCutoffGen_;
			ControlGenerator highCutoffGen_;

			ControlGenerator scaleFactorGen_;

			void computeSynthesisBlock(const SynthesisContext_ &context);


		public:

			FilteredFBCombFilter6_();

			void setLowCutoff(ControlGenerator gen) { lowCutoffGen_ = gen; };
			void setHighCutoff(ControlGenerator gen) { highCutoffGen_ = gen; };

		};

		inline void FilteredFBCombFilter6_::computeSynthesisBlock(const SynthesisContext_ &context) {

			// tick modulations
			delayTimeGen_.tick(delayTimeFrames_, context);

			TonalityFloat y = 0;
			TonalityFloat * inptr = &dryFrames_[0];
			TonalityFloat * outptr = &outputFrames_[0];
			TonalityFloat * dtptr = &delayTimeFrames_[0];

			TonalityFloat sf = scaleFactorCtrlGen_.tick(context).value;

			TonalityFloat lowCoef = cutoffToOnePoleCoef(lowCutoffGen_.tick(context).value);
			TonalityFloat hiCoef = 1.0f - cutoffToOnePoleCoef(highCutoffGen_.tick(context).value);

			for (unsigned int i = 0; i < kSynthesisBlockSize; i++) {
				onePoleLPFTick(delayLine_.tickOut(*dtptr++), lastOutLow_, lowCoef);
				onePoleHPFTick(lastOutLow_, lastOutHigh_, hiCoef);
				y = ((lastOutHigh_ * sf) + *inptr++); // no normalization on purpose
				delayLine_.tickIn(y);
				*outptr++ = y;
				delayLine_.advance();
			}

		}

	}

	// -----------------------

	// TODO: Could template-ify these for DRY-er subclassing...

	class FFCombFilter : public TemplatedEffect<FFCombFilter, Tonality_::FFCombFilter_> {

	public:

		FFCombFilter(float initialDelayTime = 0.1f, float maxDelayTime = -1);
		TONALITY_MAKE_GEN_SETTERS(FFCombFilter, delayTime, setDelayTimeGen);
		TONALITY_MAKE_CTRL_GEN_SETTERS(FFCombFilter, scaleFactor, setScaleFactorGen);
	};

	// -----

	class FBCombFilter : public TemplatedEffect<FBCombFilter, Tonality_::FBCombFilter_> {

	public:

		FBCombFilter(float initialDelayTime = 0.1f, float maxDelayTime = -1);
		TONALITY_MAKE_GEN_SETTERS(FBCombFilter, delayTime, setDelayTimeGen);
		TONALITY_MAKE_CTRL_GEN_SETTERS(FBCombFilter, scaleFactor, setScaleFactorGen);
	};

	// ------

	class FilteredFBCombFilter6 : public TemplatedEffect<FilteredFBCombFilter6, Tonality_::FilteredFBCombFilter6_>
	{
	public:
		FilteredFBCombFilter6(float initialDelayTime = 0.1f, float maxDelayTime = -1);
		TONALITY_MAKE_GEN_SETTERS(FilteredFBCombFilter6, delayTime, setDelayTimeGen);
		TONALITY_MAKE_CTRL_GEN_SETTERS(FilteredFBCombFilter6, scaleFactor, setScaleFactorGen);
		TONALITY_MAKE_CTRL_GEN_SETTERS(FilteredFBCombFilter6, lowpassCutoff, setLowCutoff);
		TONALITY_MAKE_CTRL_GEN_SETTERS(FilteredFBCombFilter6, highpassCutoff, setHighCutoff);
	};
}

#endif