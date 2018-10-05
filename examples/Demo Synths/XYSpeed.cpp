#include "Tonality.h"

using namespace Tonality;

class XYSpeed : public Synth
{
public:
	XYSpeed()
	{
		Generator speed = ControlXYSpeed().x(addParameter("x")).y(addParameter("y")).smoothed();
		Generator outputGen = RectWave()
			.freq(100 + 20 * speed)
			.pwm(0.05 + (SineWave().freq(0.1) + 1) * 0.2) * SineWave().freq(1 + 20 * speed)
			>> LPF12().cutoff(100 + 6000 * speed)
			>> StereoDelay(0.1, 0.15).wetLevel(0.1);
		;

		setOutputGen(outputGen);
	}
};

TONALITY_REGISTER_SYNTH(XYSpeed);