#ifndef SQUAREWAVE_H
#define SQUAREWAVE_H

#include "RectWave.h"

namespace Tonality
{

	// The PWM of a RectWave_ or RectWaveBL_ is 0.5 by default (square)

	// Quck-and-dirty square wave
	class SquareWave : public TemplatedGenerator<Tonality_::RectWave_> {

	public:

		TONALITY_MAKE_GEN_SETTERS(SquareWave, freq, setFrequencyGenerator);

	};

	//! Bandlimited square wave
	class SquareWaveBL : public TemplatedGenerator<Tonality_::RectWaveBL_> {

	public:

		TONALITY_MAKE_GEN_SETTERS(SquareWaveBL, freq, setFreqGen);

	};
}

#endif