#ifndef MONOTOSTEREOPANNER_H
#define MONOTOSTEREOPANNER_H

#include <iostream>
#include "Effect.h"
#include "ControlGenerator.h"

namespace Tonality {

	namespace Tonality_ {

		class MonoToStereoPanner_ : public Effect_ {

		protected:
			ControlGenerator panControlGen;
			TonalityFrames panFrames;

			void computeSynthesisBlock(const SynthesisContext_ &context);

		public:
			MonoToStereoPanner_();
			~MonoToStereoPanner_();
			void setPan(ControlGenerator);

		};

		inline void MonoToStereoPanner_::computeSynthesisBlock(const SynthesisContext_ &context) {

			TonalityFloat *synthBlockWriteHead = &outputFrames_[0];
			TonalityFloat *dryFramesReadHead = &dryFrames_[0];

			unsigned int nSamples = kSynthesisBlockSize;
			float panValue = panControlGen.tick(context).value;
			float leftVol = 1. - max(0., panValue);
			float rightVol = 1 + min(0., panValue);
			while (nSamples--) {
				*(synthBlockWriteHead++) = *dryFramesReadHead * leftVol;
				*(synthBlockWriteHead++) = *dryFramesReadHead++ * rightVol;
			}
		}

	}

	class MonoToStereoPanner : public TemplatedEffect<MonoToStereoPanner, Tonality_::MonoToStereoPanner_> {

	public:
		// pan is a -1 to 1 value
		TONALITY_MAKE_CTRL_GEN_SETTERS(MonoToStereoPanner, pan, setPan);

	};

}

#endif