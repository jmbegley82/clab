/*
 * Log.h
 * 07/25/19
 * jmb
 */

#ifndef JMLOG_H
#define JMLOG_H

#include <iostream>
#include <string>
#include <fstream>

namespace jmb {
	namespace common {
		// functions
		int SetLogFile(std::string const& file);
		//static int SetLogFile(char* file);
		// variables
		extern std::ostream* Log;
		extern std::ofstream _logFile;
	}
}

#endif //JMLOG_H
