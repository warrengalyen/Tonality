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

#include "Tonality/TonalityCore.h"
#include "Tonality/TonalityFrames.h"
#include "Tonality/SampleTable.h"
#include "Tonality/FixedValue.h"
#include "Tonality/Arithmetic.h"
#include "Tonality/ControlValue.h"
#include "Tonality/ControlTrigger.h"
#include "Tonality/ControlParameter.h"
#include "Tonality/ControlArithmetic.h"
#include "Tonality/ControlComparison.h"
#include "Tonality/MonoToStereoPanner.h"
#include "Tonality/RampedValue.h"
#include "Tonality/Synth.h"
#include "Tonality/Mixer.h"

// -------- Generators ---------

// Oscillators
#include "Tonality/TableLookupOsc.h"
#include "Tonality/SineWave.h"

#include "Tonality/SawtoothWave.h"   // Aliasing
#include "Tonality/TriangleWave.h"   // Aliasing
#include "Tonality/SquareWave.h"     // Aliasing
#include "Tonality/RectWave.h"       // Aliasing

#include "Tonality/Noise.h"

// Effects
#include "Tonality/CombFilter.h"
#include "Tonality/Filters.h"
#include "Tonality/StereoDelay.h"
#include "Tonality/BasicDelay.h"
#include "Tonality/Reverb.h"
#include "Tonality/FilterUtils.h"
#include "Tonality/DelayUtils.h"
#include "Tonality/Reverb.h"
#include "Tonality/BitCrusher.h"

// Utilities
#include "Tonality/ADSR.h"
#include "Tonality/RingBuffer.h"
#include "Tonality/LFNoise.h"

// Non-Oscillator Audio Sources
#include "Tonality/BufferPlayer.h"


// ------- Control Generators --------

#include "Tonality/ControlDelay.h"
#include "Tonality/ControlDbToLinear.h"
#include "Tonality/ControlFloor.h"
#include "Tonality/ControlPulse.h"
#include "Tonality/ControlPrinter.h"
#include "Tonality/ControlXYSpeed.h"
#include "Tonality/ControlMetro.h"
#include "Tonality/ControlMetroDivider.h"
#include "Tonality/ControlSwitcher.h"
#include "Tonality/ControlCounter.h"
#include "Tonality/ControlStepper.h"
#include "Tonality/ControlRandom.h"
#include "Tonality/ControlSnapToScale.h"
#include "Tonality/ControlMidiToFreq.h"
#include "Tonality/ControlTriggerFilter.h"
#include "Tonality/ControlCallback.h" // C++11 only

// -------- Util ---------

#include "Tonality/AudioFileUtils.h"

#endif