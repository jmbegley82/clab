/*
 * Time.cpp
 * 06/11/2019
 * Copyright JMB
 *
 */

//#include <SDL_timer.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <cassert>
#include "Time.h"

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
			timespec currentTime;
			clock_gettime(CLOCK_MONOTONIC_RAW, &currentTime);
			//gettimeofday(&currentTime, NULL);
			retval = currentTime.tv_sec * 1000;
			retval += currentTime.tv_nsec / 1000000;
			return retval;
		}

		void SleepMsec(int ms) {
			if(ms > 0) usleep(ms*1000);
			else std::cout << "Debug Time:  fuck." << std::endl;
		}

		void SleepMsec(double ms) {
			if(ms > 0) usleep(ms*1000.0);
			else std::cout << "Debug Time:  doublefuck." << std::endl;
		}
	}

}
