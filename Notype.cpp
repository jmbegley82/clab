/*
 *  Notype.cpp
 *  Test
 *
 *  Created by james on 7/18/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include "Notype.h"

namespace jmb {

	namespace common {
		
		const char Notype::type = 0xFE;
		
		Notype::Notype() {
			Notype("");
		}
		
		Notype::Notype(std::string const& name) : Atom(name){
			_type = type;
		}
		
		Notype::~Notype() {
		}
	}
	
}