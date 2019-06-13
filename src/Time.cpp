/*
 * Time.cpp
 * 06/11/2019
 * Copyright JMB
 *
 */

#include <SDL_timer.h>
#include "Time.h"

namespace jmb {

	namespace common {

		int GetTimeInMsec() {
			return SDL_GetTicks();
		}

		void SleepMsec(int ms) {
			SDL_Delay(ms);
		}
	}

}
