#include "Tonality.h"

using namespace Tonality;

class BandlimitedOscillatorTest : public Synth
{
public:

	BandlimitedOscillatorTest()
	{
		ControlParameter blend = addParameter("blend").min(0).max(1);

		Generator freqSweep = SineWave().freq(0.25) * 1000 + 1080;
		Generator smoothBlend = blend.smoothed();

		Generator output = (SquareWave().freq(freqSweep) * (1.0 - smoothBlend)) + (SquareWaveBL().freq(freqSweep) * smoothBlend);
		setOutputGen(output * 0.25);
	}
};

TONALITY_REGISTER_SYNTH(BandlimitedOscillatorTest);
