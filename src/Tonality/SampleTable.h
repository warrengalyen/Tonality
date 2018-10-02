// Global storage for sampled audio data - wavetables, in-memory samples, ring buffers, audio input, etc
// Allows registration of a TonalityFrames object with a name (string)

#ifndef SAMPLETABLE_H
#define SAMPLETABLE_H

#include "TonalityFrames.h"

namespace Tonality {

	namespace Tonality_ {

		class SampleTable_ {

		protected:
			TonalityFrames frames_;

		public:

			SampleTable_(unsigned int frames, unsigned int channels);

			// Property getters
			unsigned int channels() const {
				return frames_.channels();
			}

			unsigned long frames() const {
				return frames_.frames();
			}

			size_t size() const {
				return frames_.size();
			}

			// Pointer to start of data array
			TonalityFloat * dataPointer() {
				return &frames_[0];
			}

			// Resize
			void resize(unsigned int frames, unsigned int channels) {
				frames_.resize(frames, channels);
			}

			// Resample
			void resample(unsigned int frames, unsigned int channels) {
				frames_.resample(frames, channels);
			}
		};
	}

	// Access to a persistent TonalityFrames instance, so the same audio data can be read from multiple places
	class SampleTable : public TonalitySmartPointer<Tonality_::SampleTable_>
	{

	public:

		SampleTable(unsigned int nFrames = 64, unsigned int nChannels = 2) : TonalitySmartPointer<Tonality_::SampleTable_>(new Tonality_::SampleTable_(nFrames, nChannels)) {}

		// Property getters
		unsigned int channels() const {
			return obj->channels();
		}

		unsigned long frames() const {
			return obj->frames();
		}

		size_t size() const {
			return obj->size();
		}

		// Pointer to start of data array
		TonalityFloat * dataPointer() {
			return obj->dataPointer();
		}

		// Resize
		void resize(unsigned int frames, unsigned int channels) {
			obj->resize(frames, channels);
		}

		// Resample
		void resample(unsigned int frames, unsigned int channels) {
			obj->resample(frames, channels);
		}

	};
}

#endif
