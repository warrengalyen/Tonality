#ifndef LFNOISE_H
#define LFNOISE_H

#include "Generator.h"

namespace Tonality {

	namespace Tonality_ {

		class LFNoise_ : public Generator_ {

		protected:
			TonalityFrames	mFreqFrames;
			float			mSlope;
			signed long		mCounter;
			float			mLevel;

			void computeSynthesisBlock(const SynthesisContext_ &context);

		public:

			ControlGenerator	mFreq;
			void setFreq(ControlGenerator freq);
			LFNoise_();
		};

		inline void LFNoise_::computeSynthesisBlock(const SynthesisContext_ &context) {
			
			unsigned long remain = (unsigned int)outputFrames_.frames();
			TonalityFloat* out = &outputFrames_[0];

			do {
				if (mCounter <= 0) {
					mCounter = sampleRate() / std::max<float>(mFreq.tick(context).value, .001f);
					mCounter = std::max<float>(1, mCounter);
					float nextlevel = randomFloat(-1, 1);
					mSlope = (nextlevel - mLevel) / mCounter;
				}
				unsigned long nsmps = std::min(remain, (unsigned long)mCounter);
				remain -= nsmps;
				mCounter -= nsmps;
				for (int i = 0; i < nsmps; i++) {
					*(out++) = mLevel;
					mLevel += mSlope;
				}
			} while (remain);

		}
	}

	class LFNoise : public TemplatedGenerator<Tonality_::LFNoise_> {
	public:
		TONALITY_MAKE_CTRL_GEN_SETTERS(LFNoise, setFreq, setFreq);
	};
}

#endif
