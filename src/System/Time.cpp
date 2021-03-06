/*
 * Time.cpp
 * 06/11/2019
 * Copyright JMB
 *
 */

//#include <SDL_timer.h>
#include <iostream>
#include <time.h>
#if !defined _GLIBCXX_USE_CLOCK_GETTIME_SYSCALL
#include <sys/time.h>
#endif //!_GLIBCXX_USE_CLOCK_GETTIME_SYSCALL
#include <unistd.h>
#include <cassert>
#include "Time.h"
#include "Log.h"

namespace jmb {

	namespace common {

		int GetTimeInMsec() {
			//return SDL_GetTicks();
			assert(0);
			return (int)GetTimeInMsecAsDouble();
		}
		
		double GetTimeInMsecAsDouble() {
			// warning:  this will probably only work with glibc!
			double retval = 0;

#if defined _GLIBCXX_USE_CLOCK_GETTIME_SYSCALL
			timespec currentTime;
			clock_gettime(CLOCK_MONOTONIC_RAW, &currentTime);
			retval = currentTime.tv_sec * 1000;
			retval += currentTime.tv_nsec / 1000000;
#else
			// update this for non-linux platforms!
			timeval currentTime;
			gettimeofday(&currentTime, NULL);
			retval = currentTime.tv_sec * 1000;
			retval += currentTime.tv_usec / 1000;
#endif //_GLIBCXX_USE_CLOCK_GETTIME_SYSCALL
			//gettimeofday(&currentTime, NULL);

			return retval;
		}

		void SleepMsec(int ms) {
			if(ms > 0) usleep(ms*1000);
			else *Log << "Debug Time:  fuck." << std::endl;
		}

		void SleepMsec(double ms) {
			if(ms > 0) usleep(ms*1000.0);
			else *Log << "Debug Time:  doublefuck." << std::endl;
		}
	}

}
