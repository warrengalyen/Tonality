#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "Effect.h"
#include "SampleTable.h"

namespace Tonality {

	namespace Tonality_ {

		class RingBuffer_ : public SampleTable_ {

		private:

			unsigned long readHead_;
			unsigned long writeHead_;

		public:

			RingBuffer_(unsigned int frames, unsigned int channels);
			void write(float * data, unsigned int nFrames, unsigned int nChannels);
			void read(TonalityFrames & outFrames);
			void reset();

		};

		inline void RingBuffer_::write(TonalityFloat *data, unsigned int nFrames, unsigned int nChannels) {

#ifdef TONALITY_DEBUG
			// Detect overrun
			unsigned long finalWriteHead = (writeHead_ + nFrames) % frames();
			if (finalWriteHead >= readHead_ && (writeHead_ < readHead_ || finalWriteHead < writeHead_)) {
				warning("RingBuffer overrun detected");
			}
#endif

			TonalityFloat *writeptr = &frames_(writeHead_, 0);

			unsigned int bufChannels = channels();
			unsigned long bufFrames = frames();

			if (bufChannels == nChannels) {

				for (unsigned int i = 0; i < nFrames; i++) {
					for (unsigned int c = 0; c < nChannels; c++) {
						*writeptr++ = *data++;
					}
					if (++writeHead_ >= bufFrames) {
						writeHead_ = 0;
						writeptr = &frames_[0];
					}
				}

			}
			else if (bufChannels > nChannels) {
				for (unsigned int i = 0; i < nFrames; i++) {
					for (unsigned int c = 0; c < bufChannels; c++) {
						*writeptr++ = *data;
					}
					data++;
					if (++writeHead_ >= bufFrames) {
						writeHead_ = 0;
						writeptr = &frames_[0];
					}
				}
			}
			else {
				for (unsigned int i = 0; i < nFrames; i++) {
					*writeptr = 0;
					for (unsigned int c = 0; c < nChannels; c++) {
						*writeptr += *data++;
					}
					*writeptr++ /= (float)nChannels;
					if (++writeHead_ >= bufFrames) {
						writeHead_ = 0;
						writeptr = &frames_[0];
					}
				}
			}

		}

		inline void RingBuffer_::read(TonalityFrames & outFrames) {

#ifdef TONALITY_DEBUG
			// Detect underrun
			unsigned long finalReadHead = (readHead_ + outFrames.frames()) % frames();
			if (finalReadHead > writeHead_ && (readHead_ < writeHead_ || finalReadHead < readHead_)) {
				warning("RingBuffer underrun detected");
			}
#endif

			TonalityFloat *readptr = &frames_(readHead_, 0);
			TonalityFloat *outptr = &outFrames[0];

			unsigned long nFrames = outFrames.frames();
			unsigned int nChannels = outFrames.channels();

			unsigned long bufFrames = frames();
			unsigned int bufChannels = channels();

			if (bufChannels == nChannels) {

				for (unsigned int i = 0; i < nFrames; i++) {
					for (unsigned int c = 0; c < nChannels; c++) {
						*outptr++ = *readptr++;
					}
					if (++readHead_ >= bufFrames) {
						readHead_ = 0;
						readptr = &frames_[0];
					}
				}

			}
			else if (bufChannels > nChannels) {
				for (unsigned int i = 0; i < nFrames; i++) {
					*outptr = 0;
					for (unsigned int c = 0; c < bufChannels; c++) {
						*outptr += *readptr++;
					}
					*outptr /= (float)bufChannels;
					outptr++;
					if (++readHead_ >= bufFrames) {
						readHead_ = 0;
						readptr = &frames_[0];
					}
				}
			}
			else {
				for (unsigned int i = 0; i < nFrames; i++) {
					for (unsigned int c = 0; c < nChannels; c++) {
						*outptr++ = *readptr;
					}
					readptr++;
					if (++readHead_ >= bufFrames) {
						readHead_ = 0;
						readptr = &frames_[0];
					}
				}
			}

		}

		inline void RingBuffer_::reset() {
			readHead_ = 0;
			writeHead_ = 0;
		}

	}


	// ----------- Ring Buffer Data Container -----------

	//! Like a SampleTable_, but with counters for over/underrun detection and easy synchronous read/write
	//  TODO: Maybe should template the SampleTable smart pointer instead of statically casting the object?
	class RingBuffer : public SampleTable {

	public:

		RingBuffer(unsigned int nFrames = 64, unsigned int nChannels = 2) {
			delete obj;
			obj = new Tonality_::RingBuffer_(nFrames, nChannels);
		}

		void write(TonalityFloat * data, unsigned int nFrames, unsigned int nChannels) {
			static_cast<Tonality_::RingBuffer_*>(obj)->write(data, nFrames, nChannels);
		}

		void read(TonalityFrames & outFrames) {
			static_cast<Tonality_::RingBuffer_*>(obj)->read(outFrames);
		}

		void reset() {
			static_cast<Tonality_::RingBuffer_*>(obj)->reset();
		}

	};



	namespace Tonality_ {

		class RingBufferReader_ : public Generator_ {

		protected:

			RingBuffer ringBuffer_;

		public:

			void setRingBuffer(RingBuffer buffer) {
				setIsStereoOutput(buffer.channels() == 2);
				ringBuffer_ = buffer;
			}

			void computeSynthesisBlock(const SynthesisContext_ &context);

		};

		inline void RingBufferReader_::computeSynthesisBlock(const SynthesisContext_ &context) {
			// get some output from the table
			ringBuffer_.read(outputFrames_);
		};

		// TODO: Maybe make this an Effect_?
		class RingBufferWriter_ {

		protected:

			RingBuffer ringBuffer_;
			string tableName_;

		public:

			~RingBufferWriter_();

			void initRingBuffer(string name, unsigned int nFrames, unsigned int nChannels);
			void write(float *data, unsigned int nFrames, unsigned int nChannels);
			void reset();

		};

		inline void RingBufferWriter_::write(float *data, unsigned int nFrames, unsigned int nChannels)
		{
			ringBuffer_.write(data, nFrames, nChannels);
		}

	}

	// ------

	class RingBufferReader : public TemplatedGenerator<Tonality_::RingBufferReader_> {

	public:

		RingBufferReader & bufferName(string name);

	};

	// ------

	class RingBufferWriter : public TonalitySmartPointer<Tonality_::RingBufferWriter_> {

	public:

		RingBufferWriter() : TonalitySmartPointer<Tonality_::RingBufferWriter_>(new Tonality_::RingBufferWriter_) {}
		RingBufferWriter(string name, unsigned int nFrames, unsigned int nChannels);

		void write(float *data, unsigned int nFrames, unsigned int nChannels) {
			obj->write(data, nFrames, nChannels);
		}

		void reset() {
			obj->reset();
		}
	};

}

#endif