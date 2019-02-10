/*
 *  Float.cpp
 *  Test
 *
 *  Created by james on 2/2/19.
 *  Copyright 2019 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "Float.h"
#include "Integer.h"
#include "String.h"
#include "Notype.h"

namespace jmb {

	namespace common {
		
		const char Float::type = 0x02;
		
		Float::Float() {
			Float("");
		}
		
		Float::Float(std::string const& name) : Atom(name){
			_type = Float::type;
			_data = 0.0;
		}

		Float::Float(const Atom* atm) /*: Atom(atm)*/ {
			Float(atm->identity);
			_type = Float::type;
			isEphemeral = true;
			char t = ((Atom*)atm)->GetType();
			if(t == Float::type || t == Integer::type || t == String::type) {
				_data = ReadAtom(atm);
			} else _type = Notype::type;
		}
		
		Float::~Float() {
		}
		
		void Float::SetValue(std::string const& val) {
			_data = strtod(val.c_str(), NULL);
			//std::cout << "If '" << val << "' = '" << _data <<
			//	"' Float::SetValue worked correctly on " <<
			//	GetAbsolutePath() << std::endl;
		}
		
		std::string Float::GetValueAsStdString() {
			std::string retval = "";
			char tmpc[128] = {};
			snprintf(tmpc, 128, "%16.16f", _data);
			retval += std::string(tmpc);
			return retval;
		}
		
		void Float::Debug() {
		}
		
		int Float::OperatorEqu(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Float::type) {
				_data = ReadAtom(atm);
				retval = 0;
			}
			return retval;
		}
		
		int Float::OperatorAdd(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Float::type) {
				double vald = ReadAtom(atm);
				_data += vald;
				retval = 0;
			}
			return retval;
		}
		
		int Float::OperatorSub(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Float::type) {
				double vald = ReadAtom(atm);
				_data -= vald;
				retval = 0;
			}
			return retval;
		}

		int Float::OperatorMul(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Float::type) {
				double vald = ReadAtom(atm);
				_data *= vald;
				retval = 0;
			}
			return retval;
		}

		int Float::OperatorDiv(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Float::type) {
				double vald = ReadAtom(atm);
				_data = _data / vald;
				retval = 0;
			}
			return retval;
		}

		int Float::OperatorPow(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Float::type) {
				double vald = ReadAtom(atm);
				_data = pow(_data, vald);
				retval = 0;
			}
			return retval;
		}

		int Float::_Procedure() {
			int retval = -1;
			return retval;
		}
		
		Atom* Float::_Interpret(Atom* atm) {
			//std::cout << "Float::_Interpret: " << atm->identity << std::endl;
			/*
			if(atm->GetType() == Float::type) return atm;
			else return new Notype(atm->identity);
			*/
			return new Float(atm);
		}

		void* Float::GetRawData() {
			return (void*)&_data;
		}

		double Float::ReadAtom(const Atom* atm) {
			char t = ((Atom*)atm)->GetType();
			if(t == Float::type)
				return *(double*)((Float*)atm)->GetRawData();
			else if(t == Integer::type)
				return (double)(*(int*)((Integer*)atm)->GetRawData());
			else if(t == String::type) {
				std::string tmps = ((String*)atm)->GetValueAsStdString();
				return strtod(tmps.c_str(), NULL);
			} else
				return 0.0;
		}

	}
	
}
