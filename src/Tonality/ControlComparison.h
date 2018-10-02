/**************************************************
 *
 *  For all comparison operators, only the lhs will
 *  drive new triggers at the output. This allows
 *  for trigger routing based on satisfying a
 *  condition.
 *
 *  Output is either 0 or 1.
 *
 ***************************************************/

#ifndef CONTROLCOMPARISON_H
#define CONTROLCOMPARISON_H

#include "ControlValue.h"

namespace Tonality {

	// --------------------------------------
	//   BASE COMPARISON CONTROLGENERATOR
	// --------------------------------------

	namespace Tonality_ {

		class ControlComparisonOperator_ : public ControlGenerator_ {

		protected:

			ControlGenerator lhsGen_;
			ControlGenerator rhsGen_;

			virtual bool satisfiesCondition(TonalityFloat l, TonalityFloat r) = 0;
			void computeOutput(const SynthesisContext_ & context);

		public:

			ControlComparisonOperator_();

			void setLeft(ControlGenerator gen) { lhsGen_ = gen; }
			void setRight(ControlGenerator gen) { rhsGen_ = gen; }

		};

		inline void ControlComparisonOperator_::computeOutput(const SynthesisContext_ & context) {

			output_.triggered = false;

			ControlGeneratorOutput lhsOut = lhsGen_.tick(context);
			ControlGeneratorOutput rhsOut = rhsGen_.tick(context);
			if (lhsOut.triggered) {
				output_.value = satisfiesCondition(lhsOut.value, rhsOut.value) ? 1.0f : 0.0f;
				output_.triggered = true;
			}
			else {
				output_.value = 0;
			}

		}

	}

	template <class OperatorType>
	class TemplatedControlComparisonOperator : public TemplatedControlGenerator<OperatorType> {

	public:

		void setLeft(ControlGenerator gen) {
			this->gen()->setLeft(gen);
		}

		void setRight(ControlGenerator gen) {
			this->gen()->setRight(gen);
		}

	};

	// --------------------------------------
	//              EQUALITY
	// --------------------------------------

	namespace Tonality_ {

		class ControlEquals_ : public ControlComparisonOperator_ {

		protected:

			inline bool satisfiesCondition(TonalityFloat l, TonalityFloat r)
			{
				return l == r;
			}

		};

	}

	class ControlEquals : public TemplatedControlComparisonOperator<Tonality_::ControlEquals_> {};

	static ControlEquals operator == (ControlGenerator lhs, ControlGenerator rhs) {
		ControlEquals c;
		c.setLeft(lhs);
		c.setRight(rhs);
		return c;
	}

	static ControlEquals operator == (ControlGenerator lhs, TonalityFloat right) {
		ControlEquals c;
		c.setLeft(lhs);
		c.setRight(ControlValue(right));
		return c;
	}

	// --------------------------------------
	//             INEQUALITY
	// --------------------------------------

	namespace Tonality_ {

		class ControlNotEquals_ : public ControlComparisonOperator_ {

		protected:

			inline bool satisfiesCondition(TonalityFloat l, TonalityFloat r)
			{
				return l != r;
			}

		};
	}

	class ControlNotEquals : public TemplatedControlComparisonOperator<Tonality_::ControlNotEquals_> {};

	static ControlNotEquals operator != (ControlGenerator lhs, ControlGenerator rhs) {
		ControlNotEquals c;
		c.setLeft(lhs);
		c.setRight(rhs);
		return c;
	}

	static ControlNotEquals operator != (ControlGenerator lhs, TonalityFloat right) {
		ControlNotEquals c;
		c.setLeft(lhs);
		c.setRight(ControlValue(right));
		return c;
	}

	// --------------------------------------
	//            GREATER THAN
	// --------------------------------------

	namespace Tonality_ {

		class ControlGreaterThan_ : public ControlComparisonOperator_ {

		protected:

			inline bool satisfiesCondition(TonalityFloat l, TonalityFloat r)
			{
				return l > r;
			}

		};

	}

	class ControlGreaterThan : public TemplatedControlComparisonOperator<Tonality_::ControlGreaterThan_> {};

	static ControlGreaterThan operator > (ControlGenerator lhs, ControlGenerator rhs) {
		ControlGreaterThan c;
		c.setLeft(lhs);
		c.setRight(rhs);
		return c;
	}

	static ControlGreaterThan operator > (ControlGenerator lhs, TonalityFloat right) {
		ControlGreaterThan c;
		c.setLeft(lhs);
		c.setRight(ControlValue(right));
		return c;
	}

	// --------------------------------------
	//          GREATER OR EQUAL
	// --------------------------------------

	namespace Tonality_ {

		class ControlGreaterOrEqual_ : public ControlComparisonOperator_ {

		protected:

			inline bool satisfiesCondition(TonalityFloat l, TonalityFloat r)
			{
				return l >= r;
			}

		};

	}

	class ControlGreaterOrEqual : public TemplatedControlComparisonOperator<Tonality_::ControlGreaterOrEqual_> {};

	static ControlGreaterOrEqual operator >= (ControlGenerator lhs, ControlGenerator rhs) {
		ControlGreaterOrEqual c;
		c.setLeft(lhs);
		c.setRight(rhs);
		return c;
	}

	static ControlGreaterOrEqual operator >= (ControlGenerator lhs, TonalityFloat right) {
		ControlGreaterOrEqual c;
		c.setLeft(lhs);
		c.setRight(ControlValue(right));
		return c;
	}

	// --------------------------------------
	//              LESS THAN
	// --------------------------------------

	namespace Tonality_ {

		class ControlLessThan_ : public ControlComparisonOperator_ {

		protected:

			inline bool satisfiesCondition(TonalityFloat l, TonalityFloat r)
			{
				return l < r;
			}

		};

	}

	class ControlLessThan : public TemplatedControlComparisonOperator<Tonality_::ControlLessThan_> {};

	static ControlLessThan operator < (ControlGenerator lhs, ControlGenerator rhs) {
		ControlLessThan c;
		c.setLeft(lhs);
		c.setRight(rhs);
		return c;
	}

	static ControlLessThan operator < (ControlGenerator lhs, TonalityFloat right) {
		ControlLessThan c;
		c.setLeft(lhs);
		c.setRight(ControlValue(right));
		return c;
	}

	// --------------------------------------
	//           LESS OR EQUAL
	// --------------------------------------

	namespace Tonality_ {

		class ControlLessOrEqual_ : public ControlComparisonOperator_ {

		protected:

			inline bool satisfiesCondition(TonalityFloat l, TonalityFloat r)
			{
				return l <= r;
			}

		};

	}

	class ControlLessOrEqual : public TemplatedControlComparisonOperator<Tonality_::ControlLessOrEqual_> {};

	static ControlLessOrEqual operator <= (ControlGenerator lhs, ControlGenerator rhs) {
		ControlLessOrEqual c;
		c.setLeft(lhs);
		c.setRight(rhs);
		return c;
	}

	static ControlLessOrEqual operator <= (ControlGenerator lhs, TonalityFloat right) {
		ControlLessOrEqual c;
		c.setLeft(lhs);
		c.setRight(ControlValue(right));
		return c;
	}

}

#endif