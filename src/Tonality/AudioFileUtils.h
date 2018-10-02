#ifndef AUDIOFILEUTILS_H
#define AUDIOFILEUTILS_H

#include "SampleTable.h"

namespace Tonality {

	SampleTable loadAudioFile(string path, int numChannels = 2);
}

#endif // AUDIOFILEUTILS_H
