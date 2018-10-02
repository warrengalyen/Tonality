#ifndef TRIANGLEWAVE_H
#define TRIANGLEWAVE_H

#include "SawtoothWave.h"

namespace Tonality {

	// Quick-and-dirty triangle wave.
	class TriangleWave : public TemplatedGenerator<Tonality_::AngularWave_>
	{

	public:

		TriangleWave() {
			gen()->setSlopeGenerator(FixedValue(0.5f));
		}

		TONALITY_MAKE_GEN_SETTERS(TriangleWave, freq, setFrequencyGenerator);

		//! Set from 0-1 to change slope. At 0, it's a falling saw, at 1, it's a rising saw (defaults to 0.5, triangle)
		TONALITY_MAKE_GEN_SETTERS(TriangleWave, slope, setSlopeGenerator);

	};

}

#endif