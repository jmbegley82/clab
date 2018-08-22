/*
 *  Integer.cpp
 *  Test
 *
 *  Created by james on 8/11/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <assert.h>
#include <math.h>
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
			_data = (int)round(strtod(val.c_str(), NULL));
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
		
		int Integer::OperatorAdd(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Integer::type) {
				std::string vals = atm->GetValueAsStdString();
				int vali = (int)round(strtod(vals.c_str(), NULL));
				_data += vali;
				retval = 0;
			} else assert(0);
			return retval;
		}
		
		int Integer::OperatorSub(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Integer::type) {
				std::string vals = atm->GetValueAsStdString();
				int vali = (int)round(strtod(vals.c_str(), NULL));
				_data -= vali;
				retval = 0;
			} else assert(0);
			return retval;
		}

		int Integer::OperatorMul(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Integer::type) {
				std::string vals = atm->GetValueAsStdString();
				int vali = (int)round(strtod(vals.c_str(), NULL));
				_data *= vali;
				retval = 0;
			} else assert(0);
			return retval;
		}

		int Integer::OperatorDiv(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Integer::type) {
				std::string vals = atm->GetValueAsStdString();
				int vali = (int)round(strtod(vals.c_str(), NULL));
				_data /= vali;
				retval = 0;
			} else assert(0);
			return retval;
		}

		int Integer::OperatorPow(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Integer::type) {
				std::string vals = atm->GetValueAsStdString();
				int vali = (int)round(strtod(vals.c_str(), NULL));
				_data = pow(_data, vali);
				retval = 0;
			} else assert(0);
			return retval;
		}

		int Integer::_Procedure() {
			int retval = -1;
			return retval;
		}
		
		Atom* Integer::_Interpret(Atom* atm) {
			//std::cout << "Integer::_Interpret: " << atm->identity << std::endl;
			if(atm->GetType() == Integer::type) return atm;
			else return new Notype(atm->identity);
		}
	}
	
}
