#include "ControlChangeNotifier.h"

namespace Tonality {
	namespace Tonality_ {

		ControlChangeNotifier_::ControlChangeNotifier_() : outputReadyToBeSentToUI(false) {

		}

		ControlChangeNotifier_::~ControlChangeNotifier_() {

		}

		void ControlChangeNotifier_::computeOutput(const SynthesisContext_ & context) {
			output_ = input_.tick(context);
			if (output_.triggered) {
				outputReadyToBeSentToUI = false; // maybe silly, but a tiny bit of atomicness/thread safety here
				outputToSendToUI = output_;
				outputReadyToBeSentToUI = true;
			}
		}

		void  ControlChangeNotifier_::sendControlChangesToSubscribers() {
			if (outputReadyToBeSentToUI) {
				for (vector<ControlChangeSubscriber*>::iterator it = subscribers.begin(); it != subscribers.end(); it++) {
					(*it)->valueChanged(name, outputToSendToUI.value);
				}
				outputReadyToBeSentToUI = false;
			}
		}

		void ControlChangeNotifier_::addValueChangedSubscriber(ControlChangeSubscriber* sub) {
			subscribers.push_back(sub);
		}


		void ControlChangeNotifier_::removeValueChangedSubscriber(ControlChangeSubscriber* sub) {
			subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), sub), subscribers.end());
		}

	} // Namespace Tonality_


	void ControlChangeNotifier::sendControlChangesToSubscribers() {
		gen()->sendControlChangesToSubscribers();
	}

} // Namespace Tonality