/*
 *  Integer.cpp
 *  Test
 *
 *  Created by james on 8/11/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>
#include "Integer.h"
#include "Float.h"
#include "String.h"
#include "Notype.h"
#include "StrSplit.h"

namespace jmb {

	namespace common {
		
		const char Integer::type = 0x01;
		
		Integer::Integer() {
			Integer("");
		}
		
		Integer::Integer(std::string const& name) : Atom(name){
			_type = Integer::type;
			_data = 0;
		}

		Integer::Integer(const Atom* atm) /*: Atom(atm)*/ {
			Integer(atm->identity);
			_type = Integer::type;
			isEphemeral = true;
			char t = ((Atom*)atm)->GetType();
			if(t == Integer::type || t == Float::type
				|| t == String::type || Notype::type) {
				try {
					_data = ReadAtom(atm);
				} catch (std::invalid_argument& e) {
					std::cout << "ERROR:  " << e.what() << std::endl;
				}
			} //else assert(t == Integer::type);
			else _type = Notype::type;
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
			if(atm->GetType() == Integer::type) {
				_data = ReadAtom(atm);
			}
			return retval;
		}
		
		int Integer::OperatorAdd(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Integer::type) {
				int vali = ReadAtom(atm);
				_data += vali;
				retval = 0;
			}
			return retval;
		}
		
		int Integer::OperatorSub(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Integer::type) {
				int vali = ReadAtom(atm);
				_data -= vali;
				retval = 0;
			}
			return retval;
		}

		int Integer::OperatorMul(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Integer::type) {
				int vali = ReadAtom(atm);
				_data *= vali;
				retval = 0;
			}
			return retval;
		}

		int Integer::OperatorDiv(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Integer::type) {
				int vali = ReadAtom(atm);
				_data = (int)(_data / vali);
				retval = 0;
			}
			return retval;
		}

		int Integer::OperatorPow(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == Integer::type) {
				int vali = ReadAtom(atm);
				_data = pow(_data, vali);
				retval = 0;
			}
			return retval;
		}

		int Integer::_Procedure() {
			int retval = -1;
			return retval;
		}
		
		Atom* Integer::_Interpret(Atom* atm) {
			//std::cout << "Integer::_Interpret: " << atm->identity << std::endl;
			/*
			if(atm->GetType() == Integer::type) return atm;
			else return new Notype(atm->identity);
			*/
			return new Integer(atm);
		}

		void* Integer::GetRawData() {
			return (void*)&_data;
		}

		int Integer::ReadAtom(const Atom* atm) {
			char t = ((Atom*)atm)->GetType();
			if(t == Integer::type)
				return *(int*)((Integer*)atm)->GetRawData();
			else if(t == Float::type)
				return round(*(double*)((Float*)atm)->GetRawData());
			else if(t == String::type) {
				std::string str = ((String*)atm)->GetValueAsStdString();
				if(!ValidateStrtod(str)) throw std::invalid_argument("Could not convert String to Integer:  " + str);
				return round(strtod(str.c_str(), NULL));
			} else if(t == Notype::type) {
				if(!ValidateStrtod(atm->identity)) throw std::invalid_argument("Could not convert Literal to Integer:  " + atm->identity);
				return (int)strtod(atm->identity.c_str(), NULL);
			}
			else return 0;
		}
	}
	
}
