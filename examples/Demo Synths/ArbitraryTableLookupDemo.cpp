#include "Tonality.h"

using namespace Tonality;

class ArbitraryTableLookupSynth : public Synth
{
	ArbitraryTableLookupSynth()
	{
		/* Build a table of arbitrary length. TableLookupOsc requires power-of-two + 1
		 * length tables but they will be resized if necessary.
		 * Try changing this to 2049 and compare the sound. Should be perceptually
		 * almost identical.
		*/
		const unsigned int tablesize = 2500;

		// You can register this in a collection if you want to use it in a few oscillators
		SampleTable lookupTable = SampleTable(tablesize, 1);

		TonalityFloat norm = 1.0f / tablesize;
		TonalityFloat * tableData = lookupTable.dataPointer();
		for (unsigned int i = 0; i < tablesize; i++)
		{
			// sum a few sine waves
			TonalityFloat phase = TWO_PI * i * norm;
			*tableData++ = 0.75f * sinf(phase) + 0.5f * sinf(phase * 2) + 0.25f * sinf(phase * 5);
		}

		TableLookupOsc osc = TableLookupOsc().setLookupTable(lookupTable).freq(100 + 40 * SineWave().freq(0.1));

		setOutputGen(osc * 0.25);
	}
};

TONALITY_REGISTER_SYNTH(ArbitraryTableLookupSynth);