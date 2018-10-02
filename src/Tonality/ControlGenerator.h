#ifndef CONTROLGENERATOR_H
#define CONTROLGENERATOR_H

#include "TonalityCore.h"

namespace Tonality {

	struct ControlGeneratorOutput {
		TonalityFloat	value;
		bool			triggered;

		ControlGeneratorOutput() : value(0), triggered(false) {};
	};

	namespace Tonality_ {

		class ControlGenerator_ {

		public:

			ControlGenerator_();
			virtual ~ControlGenerator_();

			// mutex for swapping inputs, etc.
			void lockMutex();
			void unlockMutex();

			// Only override tick if you need custom reuse behavior
			// Pass in a pointer to a TonalityFloat to turen a value. Some generators may not care about value.
			virtual ControlGeneratorOutput tick(const SynthesisContext_ & context);

			// Used for initializing other generators (see smoothed() method for example)
			virtual ControlGeneratorOutput initialOutput();

		protected:

			// Override this function to implement a new ControlGenerator
			/*
				 Subclasses should use this function to put new data into output_
			*/
			virtual void computeOutput(const SynthesisContext_ & context) {};

			ControlGeneratorOutput	output_;
			unsigned long			lastFrameIndex_;
		};

		inline ControlGeneratorOutput ControlGenerator_::tick(const SynthesisContext_ & context) {

			if (context.forceNewOutput || lastFrameIndex_ != context.elapsedFrames) {
				lastFrameIndex_ = context.elapsedFrames;
				computeOutput(context);
			}

#ifdef TONALITY_DEBUG
			if (output_.value != output_.value) {
				Tonality::error("ControlGenerator_::tick NaN detected.", true);
			}
#endif

			return output_;
		}
	}

	// forward declaration
	class RampedValue;

	class ControlGenerator : public TonalitySmartPointer<Tonality_::ControlGenerator_> {

	public:

		ControlGenerator(Tonality_::ControlGenerator_ * cGen = new Tonality_::ControlGenerator_) : TonalitySmartPointer<Tonality_::ControlGenerator_>(cGen) {}

		inline ControlGeneratorOutput tick(const Tonality_::SynthesisContext_ & context) {
			return obj->tick(context);
		}

		// shortcut for creating ramped value
		RampedValue smoothed(float length = 0.05);
	};

	template<class GenType>
	class TemplatedControlGenerator : public ControlGenerator {
	protected:
		GenType* gen() {
			return static_cast<GenType*>(obj);
		}

	public:
		TemplatedControlGenerator() : ControlGenerator(new GenType) {}

	};
}

#include "ControlValue.h"

#define TONALITY_MAKE_CTRL_GEN_SETTERS(generatorClassName, methodNameInGenerator, methodNameInGenerator_)\
\
generatorClassName& methodNameInGenerator(float arg){                              \
return methodNameInGenerator( ControlValue(arg) );                                 \
}                                                                                  \
\
generatorClassName& methodNameInGenerator(ControlGenerator arg){                   \
this->gen()->methodNameInGenerator_(arg);                                          \
return static_cast<generatorClassName&>(*this);                                    \
}


#endif