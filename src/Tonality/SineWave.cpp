#include "SineWave.h"

namespace Tonality {

	SineWave::SineWave() {

		static string const TONALITY_SIN_TABLE = "_TONALITY_SIN_TABLE_";

		// As soon as the first SineWave is allocated, persistent SampleTable is created. Will stay in memory for program lifetime.
		if (!Tonality_::s_oscillatorTables()->containsObjectNamed(TONALITY_SIN_TABLE)) {

			const unsigned int tableSize = 4096;

			SampleTable sineTable = SampleTable(tableSize + 1, 1);
			TonalityFloat norm = 1.0f / tableSize;
			TonalityFloat *data = sineTable.dataPointer();
			for (unsigned long i = 0; i < tableSize + 1; i++) {
				*data++ = sinf(TWO_PI * i * norm);
			}

			Tonality_::s_oscillatorTables()->insertObject(TONALITY_SIN_TABLE, sineTable);

			this->gen()->setLookupTable(sineTable);
		}
		else {
			this->gen()->setLookupTable(Tonality_::s_oscillatorTables()->objectNamed(TONALITY_SIN_TABLE));
		}
	} // Namespace Tonality
}