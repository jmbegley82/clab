/*
 * Clock.h
 * 06/16/2019
 * Copyright JMB
 *
 */

#ifndef CLOCK_H
#define CLOCK_H

namespace jmb {

	namespace common {

		class Clock {
		public:
			Clock();
			double GetTime();
		private:
			void _Init();
			double _baseTime;
		};

	}

}

#endif //CLOCK_H
