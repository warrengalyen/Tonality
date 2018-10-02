#ifndef CONTROLCHANGENOTIFIER_H
#define CONTROLCHANGENOTIFIER_H

#include "ControlGenerator.h"
#include "ControlConditioner.h"

namespace Tonality {

	// Abstract class to be extended by any class that wants to be notified of control events. 
	class ControlChangeSubscriber {
	public:
		virtual ~ControlChangeSubscriber() {}
		virtual void valueChanged(string, TonalityFloat) = 0;
	};

	namespace Tonality_ {

		class ControlChangeNotifier_ : public ControlConditioner_ {

		protected:
			void computeOutput(const SynthesisContext_ & context);
			vector<ControlChangeSubscriber*> subscribers;
			bool outputReadyToBeSentToUI;
			ControlGeneratorOutput outputToSendToUI;

		public:
			ControlChangeNotifier_();
			~ControlChangeNotifier_();
			void addValueChangedSubscriber(ControlChangeSubscriber* sub);
			void removeValueChangedSubscriber(ControlChangeSubscriber* sub);
			void sendControlChangesToSubscribers();
			string name;
		};

	}

	/*
	  A ControlChangeNotifier observes a ControlGenerator and notifies its subscribers when its value changes,
	  or when the value of its outputs "triggered" flag is true. Generally you don't instantiate this object directly,
	  rather you "publish" a controlGenerator using Synth::publishChanges(myControlGen, "nameOfMyControlGen");
	*/
	class ControlChangeNotifier : public TemplatedControlConditioner<Tonality::ControlChangeNotifier, Tonality_::ControlChangeNotifier_> {

	public:

		void sendControlChangesToSubscribers();
		void addValueChangedSubscriber(ControlChangeSubscriber* resp) { gen()->addValueChangedSubscriber(resp); };
		void removeValueChangedSubscriber(ControlChangeSubscriber* sub) { gen()->removeValueChangedSubscriber(sub); };
		void setName(string name) { gen()->name = name; }

	};
}

#endif