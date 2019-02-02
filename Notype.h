/*
 *  Notype.h
 *  Test
 *
 *  Created by james on 7/18/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef NOTYPE_H
#define NOTYPE_H

#include <string>
#include "Atom.h"

// generic type best used temporarily
// this is a great example of the simplest possible Atom-derived class

namespace jmb {
	
	namespace common {
		
		class Notype : public Atom {
		public:
			Notype();
			Notype(std::string const& name);
			Notype(const Atom* atm);
			~Notype();
			static const char type;
		};
	}
}

#endif //NOTYPE_H
