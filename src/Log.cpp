/*
 * Log.cpp
 * 07/25/19
 * jmb
 */

#include <iostream>
#include <string>
#include "Log.h"

using std::cout;
using std::string;

namespace jmb {
	namespace common {
		// variables
		std::ostream* Log;
		std::ofstream _logFile;
		
		int SetLogFile(string const& file) {
			int retval = 0;
			// first, close _logFile if applicable
			if(_logFile.is_open()) _logFile.close();
			if(file == "") {
				// empty file name sets Log back to std::cout
				Log = &cout;
			} else {
				_logFile.open(file);
				if(_logFile.is_open()) {
					Log = &_logFile;
				} else {
					Log = &cout;
					retval = -1; // unable to open file
				}
			}
			return retval;
		}
		//int SetLogFile(char* file) {
		//	return SetLogFile(string(file));
		//}

	}
}
