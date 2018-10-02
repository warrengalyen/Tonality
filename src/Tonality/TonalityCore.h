#ifndef TONALITYCORE_H
#define TONALITYCORE_H

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <limits>
#include <cstring>
#include <cstdio>
#include <cmath>

extern "C" {
	#include <stdint.h>
}

// Uncomment or define in your build configuration to log debug messages and perform extra debug checks
// #define TONALIY_DEBUG

// Determine if C++11 is available. If not, some synths cannot be used. (applies to oF demos, mostly)
#define TONALITY_HAS_CPP_11 (__cplusplus > 199711L)

// Platform-specific macros and includes
#if defined (__APPLE__)

	#import <Accelerate/Accelerate.h>
	#define USE_APPLE_ACCELERATE

#endif

#if (defined (__APPLE__) || defined (__linux__))

	#include <pthread.h> 

	#define TONALITY_MUTEX_T           pthread_mutex_t
	#define TONALITY_MUTEX_INIT(x)     pthread_mutex_init(&x, NULL)
	#define TONALITY_MUTEX_DESTROY(x)  pthread_mutex_destroy(&x)
	#define TONALITY_MUTEX_LOCK(x)     pthread_mutex_lock(&x)
	#define TONALITY_MUTEX_UNLOCK(x)   pthread_mutex_unlock(&x)

#elif (defined (_WIN32) || defined (__WIN32__))

	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>

	// Clear these macros to avoid interfering with ControlParameter::min and ::max
	#undef min
	#undef max

#if _MSC_VER < 1800
	// Windows' C90 <cmath> header does not define log2
	inline static float log2(float n) {
		return log(n) / log(2);
	}
#endif

	// Windows native mutexes
	#define TONALITY_MUTEX_T CRITICAL_SECTION
	#define TONALITY_MUTEX_INIT(x) InitializeCriticalSection(&x)
	#define TONALITY_MUTEX_DESTROY(x) DeleteCriticalSection(&x)
	#define TONALITY_MUTEX_LOCK(x) EnterCriticalSection(&x)
	#define TONALITY_MUTEX_UNLOCK(x) LeaveCriticalSection(&x)

#endif

// --- Macro for enabling denormal rounding on audio thread ---

// TODO: Any other non-SSE platforms that allow denormals by default? ARM-based targets (iPhone, for example) do not.
#if (defined (__SSE__) || defined (_WIN32))
	#include <xmmintrin.h>
	#define  TONALITY_ENABLE_DENORMAL_ROUNDING() _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON)
#else
	#define  TONALITY_ENABLE_DENORMAL_ROUNDING()
#endif


using namespace std;

typedef uint32_t              TonalityUInt32;
typedef int32_t               TonalityInt32;
typedef float                 TonalityFloat;

#ifndef PI
const TonalityFloat PI = 3.14159265358979f;
#endif

#ifndef TWO_PI
const TonalityFloat TWO_PI = 2.f * PI;
#endif

// channel indices
#define TONALITY_LEFT            0
#define TONALITY_RIGHT           1

// Causes 32nd bit in double to have fractional value 1 (decimal point on 32-bit word boundary)
// Allowing some efficient shortcuts for table lookup using power-of-two length tables
#define BIT32DECPT 1572864.0

// Top-level namespace.
/* Objects under the Tonality namespace are used to bulid synths and generator chains */
namespace Tonality {

	// DSP-level namespace
	/* Objects under the Tonality_ namespace are internal DSP-level objects not intended for public usage */
	namespace Tonality_ {

		static TonalityFloat sampleRate_ = 44100.f;
	}

	// -- Global Constants --

	// Set the operational sample rate
	/* CHANGNING WHILE RUNNING WILL RESULT IN UNDEFINED BEHAVIOR. MUST BE SET PRIOR TO OBJECT ALLOCATION */
	static void setSampleRate(TonalityFloat sampleRate) {
		Tonality_::sampleRate_ = sampleRate;
	}

	// Return sample rate
	static TonalityFloat sampleRate() {
		return Tonality_::sampleRate_;
	};

	// "Vector" size for audio processing. ControlGenerators update at this rate.
	/* THIS VALUE SHOULD BE A POWER-OF-TWO WHICH IS LESS THAN THE HARDWARE BUFFER SIZE */
	static const unsigned int kSynthesisBlockSize = 64;

	// -- Global Types --

	// For fast computation of int/fract using some bit-twiddlery
	/* inspired by the pd implementation */
	union FastPhasor {
		double d;
		TonalityInt32 i[2];
	};


	namespace Tonality_ {

		// Context which defines a particular synthesis graph

		/*
			Context passed down from root BufferFiller graph object to all sub-generators.
			synchronizes signal flow in cases when generator output is shared between multiple inputs
		*/
		struct SynthesisContext_ {
			
			// Number of frames elapsed since context start
			// unsigned long will last 38+ days before overflow at 44.1 kHz
			unsigned long elapsedFrames;

			// Elapsed time since context start
			double elapsedTime;

			// If true, generators will be forced to compute fresh output
			// TODO: Not fully implemented yet
			bool forceNewOutput;

			SynthesisContext_() : elapsedFrames(0), elapsedTime(0), forceNewOutput(true) {}

			void tick() {
				elapsedFrames += kSynthesisBlockSize;
				elapsedTime = (double)elapsedFrames / sampleRate();
				forceNewOutput = false;
			};
		};
	
	} // namespace Tonality_

	// Dummy context for ticking things in-place.
	// Will always be at time 0, forceNewOutput == true
	static const Tonality_::SynthesisContext_ DummyContext;

#pragma mark - Utility Functions

	//-- Vector Math --
	inline static void vcopy(TonalityFloat * dst, unsigned int dst_str, const TonalityFloat * src, unsigned int src_str, unsigned int length) {
		for (unsigned int i = 0; i < length; i++, dst += dst_str, src += src_str) {
			*dst = *src;
		}
	}

	//-- Arithmetic --
	
	inline static TonalityFloat max(TonalityFloat a, TonalityFloat b) {
		return (a > b ? a : b);
	}

	inline static TonalityFloat min(TonalityFloat a, TonalityFloat b) {
		return (a < b ? a : b);
	}

	inline static TonalityFloat clamp(TonalityFloat val, TonalityFloat min, TonalityFloat max) {
		return (val < min ? min : (val > max ? max : val));
	}

	inline static TonalityFloat map(TonalityFloat val, TonalityFloat inMin, TonalityFloat inMax, TonalityFloat outMin, TonalityFloat outMax, bool clamp = true) {
		TonalityFloat result = ((val - inMin) / (inMax - inMin)) * (outMax - outMin) + outMin;
		if (clamp) {
			result = Tonality::clamp(result, min(outMin, outMax), max(outMin, outMax));
		}
		return result;
	}

	inline static TonalityFloat lerp(TonalityFloat x1, TonalityFloat x2, TonalityFloat f) {
		return (x1 + f * (x2 - x1));
	}

	inline TonalityFloat sinc(float x)
	{
		TonalityFloat pi_x;

		if (x == 0.0f)
			return 1.0f;
		else
		{
			pi_x = PI * x;
			return sinf(pi_x) / pi_x;
		}
	}

	inline bool isPowerOf2(unsigned int input, unsigned int * prevPo2) {

		if (input == 0) return true;

		unsigned int po2 = 2;
		while (po2 < input) {
			po2 *= 2;
		}

		if (prevPo2) {

			unsigned int nextPo2 = po2 * 2;
			*prevPo2 = abs((int)input - (int)po2) < abs((int)input - (int)nextPo2) ? po2 : nextPo2;
		}

		return input == po2;
	}

	#define TONALITY_LOG_MAP_BASEVAL -4

	// Takes linear value 0-1, maps to logarithmic value (base logBase) scaled to min-max. Useful for making faders.
	inline static TonalityFloat mapLinToLog(float linValue, float min, float max) {
		float expValue = map(linValue, 0.f, 1.f, TONALITY_LOG_MAP_BASEVAL, 0.f, true);
		return map(powf(10.f, expValue), 0.0001f, 1.0f, min, max, true);
	}

	// Takes logarithmic value between min-max, maps to linear value 0-1. Useful for making faders.
	inline static TonalityFloat mapLogToLin(float logValue, float min, float max) {
		return map(log10f(map(logValue, min, max, 0.0001f, 1.f, true)), TONALITY_LOG_MAP_BASEVAL, 0.f, 0.f, 1.f, true);
	}

	//-- Freq/MIDI --

	//! Midi note number to frequency in Hz
	inline static TonalityFloat mtof(TonalityFloat nn) {
		return 440.0f * powf(2.0f, (nn - 69.0f) / 12.0f);
	}

	//! Frequency in Hz to midi note number
	inline static TonalityFloat ftom(TonalityFloat f) {
		return 12.0f * (logf(f / 440.0f) / logf(2.0f)) + 69.0f;
	}

	//-- Decibels --
	/*
		Using 0 dBFS as 1.0
	*/
	inline static TonalityFloat linTodB(TonalityFloat lv) {
		return 20.0f*log10f(max(0, lv));
	}

	inline static TonalityFloat dBToLin(TonalityFloat dBFS) {
		return powf(10.f, (dBFS / 20.0f));
	}

	// -- Misc --

	inline static TonalityFloat randomSample() {
		return ((TonalityFloat)rand() / RAND_MAX) * 2.0f - 1.0f;
	}

	static float randomFloat(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}

	// Tonality exception class
	// May want to implement custom exception behavior here, but for now, this is essentially a typedef
	class TonalityException : public runtime_error
	{
		public:
			TonalityException(string const& error) : runtime_error(error) {};
	};

	// -- Logging --

	static void error(string message, bool fatal = false) {
		// maybe also log to console?
		printf("Tonality::error: %s\n", message.c_str());
		if (fatal) {
			throw TonalityException(message);
		}
	}

	static void warning(string message) {
		printf("Tonality::warning: %s\n", message.c_str());
	}

	static void debug(string message) {
#ifdef TONALITY_DEBUG
		printf("TONALITY::debug: %s\n", message.c_str());
#endif
	}

	// Dictionary helper class for registering objects by name. For correct usage, objects should be Smart Pointers.
	template<class T>
	class TonalityDictionary {
	
		protected:

			typedef std::map<string, T> TonalityDictionaryMap;
			TonalityDictionaryMap dictionaryMap_;

		public:
			
			// Add object to dictionary. Replaces old object if one exists.
			void insertObject(string name, T object) {
				dictionaryMap_[name] = object;
			}

			bool containsObjectNamed(string name) {
				typename TonalityDictionaryMap::iterator it = dictionaryMap_.find(name);
				return it != dictionaryMap_.end();
			}

			// Returns object with given name. Returns new object if no object has been set for name, does not insert it.
			T objectNamed(string name) {
				T obj;
				typename TonalityDictionaryMap::iterator it = dictionaryMap_.find(name);
				if (it != dictionaryMap_.end()) {
					obj = it->second;
				}
				return obj;
			}

			//! Remove object for name
			void removeObjectNamed(string name) {
				typename TonalityDictionaryMap::iterator it = dictionaryMap_.find(name);
				if (it != dictionaryMap_.end()) {
					dictionaryMap_.erase(it);
				}
			}
	};

	// Reference counting smart pointer class template
	template<class T>
	class TonalitySmartPointer {

		protected:

			T * obj;
			int * pcount;

		public:

			TonalitySmartPointer() : obj(NULL), pcount(NULL) {}

			TonalitySmartPointer(T * initObj) : obj(initObj), pcount(initObj ? new int(1) : NULL) {}

			TonalitySmartPointer(const TonalitySmartPointer& r) : obj(r.obj), pcount(r.pcount) {
				retain();
			}

			TonalitySmartPointer& operator=(const TonalitySmartPointer& r)
			{
				if (obj == r.obj) return *this;

				release();

				obj = r.obj;
				pcount = r.pcount;

				retain();

				return *this;
			}

			~TonalitySmartPointer() {
				release();
			}

			void retain() {
				if (pcount) (*pcount)++;
			}

			void release() {
				if (pcount && --(*pcount) == 0) {
					delete obj;
					delete pcount;

					obj = NULL;
					pcount = NULL;
				}
			}

			bool operator==(const TonalitySmartPointer& r) {
				return obj == r.obj;
			}
	};

} // namespace Tonality

#endif