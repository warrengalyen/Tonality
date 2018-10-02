#ifndef BITCRUSHER_H
#define BITCRUSHER_H

#include <iostream>

#include "Effect.h"

#include "ControlGenerator.h"

namespace Tonality {

	namespace Tonality_ {

		class BitCrusher_ : public Effect_ {

		protected:
			ControlGenerator bitDepth;

			void computeSynthesisBlock(const SynthesisContext_ &context);

		public:
			BitCrusher_();
			void setBitDepth(ControlGenerator);
			void setInput(Generator input);
			void setIsStereoInput(bool stereo);

		};

		inline void BitCrusher_::computeSynthesisBlock(const SynthesisContext_ &context) {

			TonalityFloat *synthBlockWriteHead = &outputFrames_[0];
			TonalityFloat *dryFramesReadHead = &dryFrames_[0];

			unsigned int nSamples = (unsigned int)outputFrames_.size();
			float bitDepthValue = clamp(bitDepth.tick(context).value, 0, 16);
			float bitDepthMax = pow(2, bitDepthValue);

			while (nSamples--) {
				TonalityFloat dry = *(dryFramesReadHead++);
				TonalityInt32 snapped = bitDepthMax * dry;
				TonalityFloat snappedFloat = (float)snapped / (float)bitDepthMax;
				*(synthBlockWriteHead++) = snappedFloat;
			}
		}
	}

	class BitCrusher : public TemplatedEffect<BitCrusher, Tonality_::BitCrusher_> {

	public:

		TONALITY_MAKE_CTRL_GEN_SETTERS(BitCrusher, bitDepth, setBitDepth);

	};

}

#endif 