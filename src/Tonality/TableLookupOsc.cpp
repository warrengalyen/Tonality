#include "TableLookupOsc.h"

namespace Tonality {

	namespace Tonality_ {

		TonalityDictionary<SampleTable> * s_oscillatorTables()
		{
			static TonalityDictionary<SampleTable> * s_oscillatorTables = new TonalityDictionary<SampleTable>;
			return s_oscillatorTables;
		}

		TableLookupOsc_::TableLookupOsc_() :
			phase_(0.0)
		{
			modFrames_.resize(kSynthesisBlockSize, 1);
			lookupTable_ = SampleTable(kSynthesisBlockSize, 1);
		}

		void TableLookupOsc_::reset() {
			phase_ = 0.0f;
		}

		void TableLookupOsc_::setLookupTable(SampleTable table) {
			if (table.channels() != 1) {
				error("TableLookupOsc expects lookup table with 1 channel only");
				return;
			}

			unsigned int nearestPo2;
			if (!isPowerOf2((unsigned int)table.size() - 1, &nearestPo2)) {

				warning("TableLookUpOsc lookup tables must have a (power-of-two + 1) number of samples (example 2049 or 4097). Resizing to nearest power-of-two + 1");

				table.resample(nearestPo2, 1);
				table.resize(nearestPo2 + 1, 1);
				table.dataPointer()[nearestPo2] = table.dataPointer()[0]; // copy first sample to last

			}

			lookupTable_ = table;
		}

	} // Namespace Tonality_


	TableLookupOsc & TableLookupOsc::setLookupTable(SampleTable lookupTable) {
		gen()->setLookupTable(lookupTable);
		return *this;
	}


} // Namespace Tonality