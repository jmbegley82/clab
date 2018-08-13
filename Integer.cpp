/*
 *  Integer.cpp
 *  Test
 *
 *  Created by james on 8/11/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <sstream>
#include "Integer.h"
#include "Notype.h"

namespace jmb {

	namespace common {
		
		const char Integer::type = 0x01;
		
		Integer::Integer() {
			Integer("");
		}
		
		Integer::Integer(std::string const& name) : Atom(name){
			_type = type;
			_data = 0;
		}
		
		Integer::~Integer() {
		}
		
		void Integer::SetValue(std::string const& val) {
			_data = strtod(val.c_str(), NULL);
			//std::cout << "If '" << val << "' = '" << _data <<
			//	"' Integer::SetValue worked correctly on " <<
			//	GetAbsolutePath() << std::endl;
		}
		
		std::string Integer::GetValueAsStdString() {
			std::string retval = "";
			char tmpc[128] = {};
			snprintf(tmpc, 128, "%d", _data);
			retval += tmpc;
			return retval;
		}
		
		void Integer::Debug() {
		}
		
		int Integer::OperatorEqu(Atom* atm) {
			int retval = -1;
			std::cout << "Integer::OperatorEqu: " << atm->identity << " is ";
			if(atm->GetType() == Integer::type) {
				std::cout << "an Integer";
				std::string val = atm->GetValueAsStdString();
				std::cout << " with value '" << val << "'";
				SetValue(val);
				retval = 0;
			} else if(atm->GetType() == Notype::type) {
				std::cout << "a Notype";
			} else {
				std::cout << "not any type known to this object";
			}
			std::cout << std::endl;
			return retval;
		}
		
		int Integer::_Procedure() {
			int retval = -1;
			return retval;
		}
		
		Atom* Integer::_Interpret(Atom* atm) {
			std::cout << "Integer::_Interpret: " << atm->identity << std::endl;
			if(atm->GetType() == Integer::type) return atm;
			else return new Notype(atm->identity);
		}
	}
	
}