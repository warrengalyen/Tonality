#ifndef GENERATOR_H
#define GENERATOR_H

#include "TonalityFrames.h"
#include <cmath>

namespace Tonality {

	namespace Tonality_ {

		class Generator_ {
		
		public:

			Generator_();
			virtual ~Generator_();

			virtual void tick(TonalityFrames& frames, const SynthesisContext_ &context);

			bool isStereoOutput() { return isStereoOutput_; };

			// set stereo/mono - changes number of channels in outputFrames_
			// subclass should call in constructor to determine channel output
			virtual void setIsStereoOutput(bool stereo);

		protected:

			// override point for defining generator behavior
			// subclass should implement to fill frames with new data
			virtual void computeSynthesisBlock(const SynthesisContext_ &context) {};

			bool			isStereoOutput_;
			TonalityFrames	outputFrames_;
			unsigned long	lastFrameIndex_;

		};

		inline void Generator_::tick(TonalityFrames &frames, const SynthesisContext_ &context) {

			// check context to see if we need new frames
			if (context.forceNewOutput || lastFrameIndex_ != context.elapsedFrames) {
				computeSynthesisBlock(context);
				lastFrameIndex_ = context.elapsedFrames;
			}

			// copy synthesis block to frames passed in
			frames.copy(outputFrames_);
		}
	}

	class Generator : public TonalitySmartPointer<Tonality_::Generator_> {
		
	public:

		Generator(Tonality_::Generator_ * gen = new Tonality_::Generator_) : TonalitySmartPointer<Tonality_::Generator_>(gen) {}

		inline bool isStereoOutput() {
			return obj->isStereoOutput();
		}

		virtual void tick(TonalityFrames& frames, const Tonality_::SynthesisContext_ & context) {
			obj->tick(frames, context);
		}
	};

	template<class GenType>
	class TemplatedGenerator : public Generator {
	protected:
		GenType* gen() {
			return static_cast<GenType*>(obj);
		}
	public:
		TemplatedGenerator() : Generator(new GenType) {}
	};
}

// Each generator should have three flavors of setter -- one that accepts a float, one that accepts a
// ControlGenerator, and one that accepts a Generator. This macro will automatically build those three
// setters

#include "FixedValue.h"

#define TONALITY_MAKE_GEN_SETTERS(generatorClassName, methodNameInGenerator, methodNameInGenerator_) \
                                                                                        \
                                                                                        \
  generatorClassName& methodNameInGenerator(Generator arg){                             \
    this->gen()->methodNameInGenerator_(arg);                                           \
    return static_cast<generatorClassName&>(*this);                                     \
  }                                                                                     \
                                                                                        \
  generatorClassName& methodNameInGenerator(float arg){                                 \
    return methodNameInGenerator( FixedValue(arg) );                                    \
  }                                                                                     \
                                                                                        \
  generatorClassName& methodNameInGenerator(ControlGenerator arg){                      \
    return methodNameInGenerator(  FixedValue().setValue(arg) );                        \
  }

#endif
