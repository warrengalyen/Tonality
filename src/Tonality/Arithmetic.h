#ifndef ADDER_H
#define ADDER_H

#include "Generator.h"

namespace Tonality {

	// -----------------------------------------
	//                 ADDER
	// -----------------------------------------

	namespace Tonality_ {

		class Adder_ : public Generator_ {

		protected:
			vector<Generator> inputs_;
			TonalityFrames workSpace_;

			void computeSynthesisBlock(const SynthesisContext_ &context);

		public:

			Adder_();

			void input(Generator generator);
			void setIsStereoOutput(bool stereo);

			Generator getInput(unsigned int index) { return inputs_[index]; };
			unsigned int numInputs() { return (unsigned int)inputs_.size(); };

		};

		inline void Adder_::computeSynthesisBlock(const SynthesisContext_ &context) {

			TonalityFloat *framesData = &outputFrames_[0];

			memset(framesData, 0, sizeof(TonalityFloat) * outputFrames_.size());

			for (int j = 0; j < inputs_.size(); j++) {
				inputs_[j].tick(workSpace_, context);
				outputFrames_ += workSpace_; // add each sample in frames to each sample in workspace
			}

		}

	}

	class Adder : public TemplatedGenerator<Tonality_::Adder_> {
	public:

		Adder input(Generator input) {
			gen()->input(input);
			return *this;
		}

		Generator operator[](unsigned int index) {
			return gen()->getInput(index);
		}

		unsigned long numInputs() {
			return gen()->numInputs();
		}

	};

	// add a Generator to another thing

	static Adder operator + (Generator a, Generator b) {
		Adder add;
		add.input(a);
		add.input(b);
		return add;
	}


	static Adder operator + (float a, Generator b) {
		Adder add;
		add.input(FixedValue(a));
		add.input(b);
		return add;
	}


	static Adder operator + (Generator a, float b) {
		Adder add;
		add.input(a);
		add.input(FixedValue(b));
		return add;
	}


	// Add a Generatator and a ControlGenerator

	static Adder operator + (Generator a, ControlGenerator b) {
		return a + FixedValue().setValue(b);
	}

	static Adder operator + (ControlGenerator a, Generator b) {
		return FixedValue().setValue(a) + b;
	}

	// Add an Adder and a ControlGenerator

	static Adder operator + (Adder a, ControlGenerator b) {
		return a + FixedValue().setValue(b);
	}

	static Adder operator + (ControlGenerator a, Adder b) {
		return FixedValue().setValue(a) + b;
	}

	// -----------------------------------------
	//                SUBTRACTOR
	// -----------------------------------------

	namespace Tonality_ {

		class Subtractor_ : public Generator_ {

		protected:

			Generator left_;
			Generator right_;
			TonalityFrames workSpace_;

			void computeSynthesisBlock(const SynthesisContext_ &context);

		public:

			Subtractor_();

			void setLeft(Generator arg);
			void setRight(Generator arg);
			void setIsStereoOutput(bool stereo);

		};

		inline void Subtractor_::computeSynthesisBlock(const SynthesisContext_ &context) {
			left_.tick(outputFrames_, context);
			right_.tick(workSpace_, context);
			outputFrames_ -= workSpace_;
		}

	}

	class Subtractor : public TemplatedGenerator<Tonality_::Subtractor_> {

	public:

		TONALITY_MAKE_GEN_SETTERS(Subtractor, left, setLeft);
		TONALITY_MAKE_GEN_SETTERS(Subtractor, right, setRight);

	};


	static Subtractor operator - (Generator a, Generator b) {
		Subtractor sub;
		sub.left(a);
		sub.right(b);
		return sub;
	}

	static Subtractor operator - (float a, Generator b) {
		Subtractor sub;
		sub.left(FixedValue(a));
		sub.right(b);
		return sub;
	}

	static Subtractor operator - (Generator a, float b) {
		Subtractor sub;
		sub.left(a);
		sub.right(FixedValue(b));
		return sub;
	}

	// Subtract a Generatator and a ControlGenerator

	static Subtractor operator - (Generator a, ControlGenerator b) {
		return a - FixedValue().setValue(b);
	}

	static Subtractor operator - (ControlGenerator a, Generator b) {
		return FixedValue().setValue(a) - b;
	}

	// -----------------------------------------
	//                MULTIPLIER
	// -----------------------------------------

	namespace Tonality_ {

		class Multiplier_ : public Generator_ {

		protected:
			vector<Generator> inputs_;
			TonalityFrames workSpace_;

			void computeSynthesisBlock(const SynthesisContext_ & context);

		public:

			Multiplier_();

			void input(Generator generator);
			void setIsStereoOutput(bool stereo);

			Generator getInput(unsigned int index) { return inputs_[index]; };
			unsigned int numInputs() { return (unsigned int)inputs_.size(); };

		};


		inline void Multiplier_::computeSynthesisBlock(const SynthesisContext_ & context) {

			memset(&outputFrames_[0], 0, sizeof(TonalityFloat) * outputFrames_.size());

			// for the first generator, store the value in the block
			inputs_[0].tick(outputFrames_, context);

			// for additional generators, use the workspace stkframes for tick, and multiply it into the frames argument
			for (int i = 1; i < inputs_.size(); i++) {
				inputs_[i].tick(workSpace_, context);
				outputFrames_ *= workSpace_;
			}

		}

	}

	class Multiplier : public TemplatedGenerator<Tonality_::Multiplier_> {
	public:
		Multiplier input(Generator inputSource) {
			gen()->input(inputSource);
			return *this;
		}

		Generator operator[](unsigned int index) {
			return gen()->getInput(index);
		}

		unsigned long numInputs() {
			return gen()->numInputs();
		}

	};

	static Multiplier operator*(Generator a, Generator b) {
		Multiplier mult;
		mult.input(a);
		mult.input(b);
		return mult;
	}

	static Multiplier operator*(float a, Generator b) {
		return FixedValue(a) * b;
	}

	static Multiplier operator*(Generator a, float b) {
		return a * FixedValue(b);
	}


	// Multiply a Generatator and a ControlGenerator

	static Multiplier operator * (Generator a, ControlGenerator b) {
		return a * FixedValue().setValue(b);
	}

	static Multiplier operator * (ControlGenerator a, Generator b) {
		return FixedValue().setValue(a) * b;
	}

	// Multiply an Multiplier and a ControlGenerator

	static Multiplier operator * (Multiplier a, ControlGenerator b) {
		return a * FixedValue().setValue(b);
	}

	static Multiplier operator * (ControlGenerator a, Multiplier b) {
		return FixedValue().setValue(a) * b;
	}

	// -----------------------------------------
	//                DIVIDER
	// -----------------------------------------

	namespace Tonality_ {

		class Divider_ : public Generator_ {

		protected:
			Generator left_;
			Generator right_;
			TonalityFrames workSpace_;

			void computeSynthesisBlock(const SynthesisContext_ &context);

		public:

			Divider_();

			void setLeft(Generator arg);
			void setRight(Generator arg);
			void setIsStereoOutput(bool stereo);

		};

		inline void Divider_::computeSynthesisBlock(const SynthesisContext_ &context) {
			left_.tick(outputFrames_, context);
			right_.tick(workSpace_, context);
			outputFrames_ /= workSpace_;

		}

	}

	class Divider : public TemplatedGenerator<Tonality_::Divider_> {

	public:
		TONALITY_MAKE_GEN_SETTERS(Divider, left, setLeft);
		TONALITY_MAKE_GEN_SETTERS(Divider, right, setRight);

	};



	static Divider operator / (Generator a, Generator b) {
		Divider div;
		div.left(a);
		div.right(b);
		return div;
	}

	static Divider operator / (float a, Generator b) {
		Divider div;
		div.left(FixedValue(a));
		div.right(b);
		return div;
	}

	static Divider operator / (Generator a, float b) {
		Divider div;
		div.left(a);
		div.right(FixedValue(b));
		return div;
	}

	// Subtract a Generatator and a ControlGenerator

	static Divider operator / (Generator a, ControlGenerator b) {
		return a / FixedValue().setValue(b);
	}

	static Divider operator / (ControlGenerator a, Generator b) {
		return FixedValue().setValue(a) / b;
	}

}

#endif
