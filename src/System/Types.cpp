/*
 * Types.cpp
 * 07/13/2019
 * JMB
 */

//#include <string>
//#include <map>
//#include "Atom.h"

#include <iostream>
#include <cassert>
#include "Types.h"
#include "Log.h"

using std::endl;
using std::string;

namespace jmb {
	namespace common {
		/*
		Types::Types() {
			_types.clear();
		}
		Types::~Types() {
		}
		*/

		namespace Types {
			void AddMapping(string const& name, Atom* (*CtorWrapper)(string)) {
				// gentlemen... BEHOLD
				// TODO:  understand why this compiles
				// TODO:  understand why/if this works
				//assert(0);
				_tmItr i = _types.find(name);
				if(i == _types.end()) {
					// add it, it's not in there
					*Log << "AddMapping:  " << name << endl;
					_types[name] = CtorWrapper;
				}
			}
			Atom* CreateNew(string const& type, string const& name) {
				Atom* retval = NULL;
				//assert(0);
				_tmItr i = _types.find(type);
				if(i != _types.end()) {
					retval = (*i->second)(name);
					*Log << "CreateNew:  " << type << " " << name << endl;
				}
				return retval;
			}
		}
	}
}
