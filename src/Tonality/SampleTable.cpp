#include "SampleTable.h"

namespace Tonality {

	namespace Tonality_ {

		SampleTable_::SampleTable_(unsigned int frames, unsigned channels) {
			frames_.resize(frames, min(channels, 2)); // limited to 2 channels
		}
	}
}