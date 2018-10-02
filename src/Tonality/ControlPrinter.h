#ifndef CONTROLPRINTER_H
#define CONTROLPRINTER_H

#include "ControlConditioner.h"

namespace Tonality {

	namespace Tonality_ {

		class ControlPrinter_ : public ControlConditioner_ {

		protected:
			void computeOutput(const SynthesisContext_ & context);

			string message;
			bool hasPrinted;

		public:
			ControlPrinter_();
			void setMessage(string message);

		};

		inline void ControlPrinter_::computeOutput(const SynthesisContext_ & context) {
			output_ = input_.tick(context);
			if (!hasPrinted || (output_.triggered)) {
				printf(message.c_str(), output_.value);
				hasPrinted = true;
			}
		}

	}

	/*
	  A controlconditioner which can be used to print the value of its input. You can set an optional format string to customize
	  the message using printf-style formatting, with exactly one %f placeholder. For example: "Current bpm is %f.";
	*/

	class ControlPrinter : public TemplatedControlConditioner<Tonality::ControlPrinter, Tonality_::ControlPrinter_> {

	public:
		ControlPrinter message(string message) {
			gen()->setMessage(message);
			return *this;
		}

	};
}

#endif