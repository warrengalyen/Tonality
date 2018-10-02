#ifndef BASICDELAY_H
#define BASICDELAY_H

#include "Effect.h"
#include "DelayUtils.h"

namespace Tonality
{
	namespace Tonality_
	{
		class BasicDelay_ : public WetDryEffect_
		{
		protected:

			Generator delayTimeGen_;
			TonalityFrames delayTimeFrames_;

			Generator fbkGen_;
			TonalityFrames fbkFrames_;

			DelayLine delayLine_;

			void computeSynthesisBlock(const SynthesisContext_& context);

		public:

			BasicDelay_();
			~BasicDelay_();

			// Overridden so output channel layout follows input channel layout
			void setInput(Generator input);

			void initialize(float delayTime, float maxDelayTime);

			void setDelayTimeGen(Generator gen) { delayTimeGen_ = gen; };

			void setFeedbackGen(Generator gen) { fbkGen_ = gen; };
		};

		inline void BasicDelay_::computeSynthesisBlock(const SynthesisContext_& context)
		{
			delayTimeGen_.tick(delayTimeFrames_, context);
			fbkGen_.tick(fbkFrames_, context);

			// input->output always has same channel layout
			unsigned int nChannels = isStereoInput() ? 2 : 1;

			TonalityFloat fbk, outSamp;
			TonalityFloat *dryptr = &dryFrames_[0];
			TonalityFloat *outptr = &outputFrames_[0];
			TonalityFloat *fbkptr = &fbkFrames_[0];
			TonalityFloat *delptr = &delayTimeFrames_[0];

			for (unsigned int i = 0; i < kSynthesisBlockSize; i++)
			{
				// Don't clamp feedback - be careful! Negative feedback could be interesting.
				fbk = *fbkptr++;

				for (unsigned int c = 0; c < nChannels; c++)
				{
					outSamp = delayLine_.tickOut(*delptr, c);
					delayLine_.tickIn(*dryptr++ + outSamp * fbk, c);
					*outptr++ = outSamp;
				}

				delptr++;
				delayLine_.advance();
			}
		}

	}

	class BasicDelay : public TemplatedWetDryEffect<BasicDelay, Tonality_::BasicDelay_>
	{
		
	public:
		// Allocating only with time argument will default max delay time to 1.5 * delayTime
		BasicDelay(float initialDelayTime = 0.5f, float maxDelayTime = -1);

		TONALITY_MAKE_GEN_SETTERS(BasicDelay, delayTime, setDelayTimeGen);

		// Warning: Feedback input is NOT clamped! Beware of feedback values greater than 1!
		TONALITY_MAKE_GEN_SETTERS(BasicDelay, feedback, setFeedbackGen);
	};
}

#endif