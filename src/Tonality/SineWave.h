#ifndef SINEWAVE_H
#define SINEWAVE_H

#include "TableLookupOsc.h"

namespace Tonality {

	class SineWave : public TemplatedGenerator<Tonality_::TableLookupOsc_> {

	public:

		SineWave();

		TONALITY_MAKE_GEN_SETTERS(SineWave, freq, setFrequency)
	};
}


#endif