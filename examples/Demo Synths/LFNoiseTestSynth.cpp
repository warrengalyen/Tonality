#include "Tonality.h"

using namespace Tonality;

class LFNoiseTestSynth : public Synth
{
public:
	LFNoiseTestSynth()
	{
		Generator outputGen = SineWave().freq(
			500 + 500 * LFNoise().setFreq(
				addParameter("noiseFreq", 100))) * 0.3;

		setOutputGen(outputGen);
	}
};

TONALITY_REGISTER_SYNTH(LFNoiseTestSynth);