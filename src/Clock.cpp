/*
 * Clock.cpp
 * 06/16/2019
 * Copyright JMB
 *
 */

#include <iostream>
#include <time.h>
#include <unistd.h>
#include <cassert>
#include "Clock.h"
#include "Time.h"

namespace jmb {

	namespace common {

		Clock::Clock() {
			_Init();
		}

		double Clock::GetTime() {
			return GetTimeInMsecAsDouble() - _baseTime;
		}

		void Clock::_Init() {
			_baseTime = GetTimeInMsecAsDouble();
		}

	}

}
