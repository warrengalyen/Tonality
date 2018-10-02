#include "BufferFiller.h"

namespace Tonality {

	namespace Tonality_ {

		BufferFiller_::BufferFiller_() : bufferReadPosition_(0) {
			TONALITY_MUTEX_INIT(mutex_);
			setIsStereoOutput(true);
		}

		BufferFiller_::~BufferFiller_() {
			TONALITY_MUTEX_DESTROY(mutex_);
		}

	}
}