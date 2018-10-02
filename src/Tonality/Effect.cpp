#include "Effect.h"

namespace Tonality
{

	namespace Tonality_
	{

		Effect_::Effect_() : isStereoInput_(false)
		{
			dryFrames_.resize(kSynthesisBlockSize, 1, 0);
			bypassGen_ = ControlValue(0);
		}

		WetDryEffect_::WetDryEffect_()
		{
			mixWorkspace_.resize(kSynthesisBlockSize, 1, 0);
			dryLevelGen_ = FixedValue(0.5);
			wetLevelGen_ = FixedValue(0.5);
		}

	}

}