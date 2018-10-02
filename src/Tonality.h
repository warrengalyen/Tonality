/***********************************************************
 *
 * Consolidated header file for Tonality core objects
 * These objects are enough to build signal chains
 * using Generators and ControlGenerators with overloaded
 * operators for arithmetic.
 *
 ***********************************************************/

#ifndef TONALITYHEADER_H
#define TONALITYHEADER_H

 // ------- Core Objects --------

#include "src/TonalityCore.h"
#include "src/TonalityFrames.h"
#include "src/SampleTable.h"
#include "src/FixedValue.h"
#include "src/Arithmetic.h"
#include "src/ControlValue.h"
#include "src/ControlTrigger.h"
#include "src/ControlParameter.h"
#include "src/ControlArithmetic.h"
#include "src/ControlComparison.h"
#include "src/MonoToStereoPanner.h"
#include "src/RampedValue.h"
#include "src/Synth.h"
#include "src/Mixer.h"

// -------- Generators ---------

// Oscillators
#include "src/TableLookupOsc.h"
#include "src/SineWave.h"

#include "src/SawtoothWave.h"   // Aliasing
#include "src/TriangleWave.h"   // Aliasing
#include "src/SquareWave.h"     // Aliasing
#include "src/RectWave.h"       // Aliasing

#include "src/Noise.h"

// Effects
#include "src/CombFilter.h"
#include "src/Filters.h"
#include "src/StereoDelay.h"
#include "src/BasicDelay.h"
#include "src/Reverb.h"
#include "src/FilterUtils.h"
#include "src/DelayUtils.h"
#include "src/Reverb.h"
#include "src/BitCrusher.h"

// Utilities
#include "src/ADSR.h"
#include "src/RingBuffer.h"
#include "src/LFNoise.h"

// Non-Oscillator Audio Sources
#include "src/BufferPlayer.h"


// ------- Control Generators --------

#include "src/ControlDelay.h"
#include "src/ControlDbToLinear.h"
#include "src/ControlFloor.h"
#include "src/ControlPulse.h"
#include "src/ControlPrinter.h"
#include "src/ControlXYSpeed.h"
#include "src/ControlMetro.h"
#include "src/ControlMetroDivider.h"
#include "src/ControlSwitcher.h"
#include "src/ControlCounter.h"
#include "src/ControlStepper.h"
#include "src/ControlRandom.h"
#include "src/ControlSnapToScale.h"
#include "src/ControlMidiToFreq.h"
#include "src/ControlTriggerFilter.h"
#include "src/ControlCallback.h" // C++11 only

// -------- Util ---------

#include "src/AudioFileUtils.h"

#endif