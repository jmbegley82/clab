/*
 * Time.h
 * 06/11/2019
 * Copyright JMB
 *
 */

#ifndef JMTIME_H
#define JMTIME_H

namespace jmb {

	namespace common {

		int GetTimeInMsec();
		double GetTimeInMsecAsDouble();
		void SleepMsec(int ms);
		void SleepMsec(double ms);

	}

}

#endif //JMTIME_H
