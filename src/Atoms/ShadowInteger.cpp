/*
 *  ShadowInteger.cpp
 *  Test
 *
 *  Created by james on 2/27/19.
 *  Copyright 2019 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>
#include "Log.h"
#include "ShadowInteger.h"
#include "Integer.h"
#include "Float.h"
#include "String.h"
#include "Notype.h"
#include "StringManip.h"

namespace jmb {

	namespace common {
		
		const char ShadowInteger::type = 0x81;
		
		ShadowInteger::ShadowInteger() {
			//ShadowInteger("", 0);
		}

		ShadowInteger::ShadowInteger(std::string const& name) {
			assert(0);
		}
		
		ShadowInteger::ShadowInteger(std::string const& name, int* addr) : Atom(name) {
			_type = ShadowInteger::type;
			hasOwnData = false;
			//*Log << "debug1:  addr=" << addr << std::endl;
			_data = addr;
			//*Log << "debug2: _data=" << *_data << std::endl;
		}

		ShadowInteger::ShadowInteger(const Atom* atm) /*: Atom(atm)*/ {
			//ShadowInteger(atm->identity, NULL);
			_type = ShadowInteger::type;
			_data = new int;
			isEphemeral = true;
			eraseMe = atm->eraseMe;
			hasOwnData = true;
			containsValidData = true;
			char t = ((Atom*)atm)->GetType();
			if(t == ShadowInteger::type || t == Float::type
				|| t == Integer::type || t == String::type
				|| t == Notype::type) {
				try {
					*_data = ReadAtom(atm);
				} catch (std::invalid_argument& e) {
					*Log << "ERROR:  " << e.what() << std::endl;
					containsValidData = false;
				}
			} //else assert(t == ShadowInteger::type);
			else _type = Notype::type;
		}
		
		ShadowInteger::~ShadowInteger() {
			if(hasOwnData) delete _data;
		}

		Atom* ShadowInteger::CtorWrapper(std::string name) {
			// this seems unnecessary
			return new ShadowInteger(name);
		}

		int ShadowInteger::Command(std::string const& cmd) {
			if(cmd == "clear") {
				*_data = 0;
				return 0;
			} else return Atom::Command(cmd);
		}

		void ShadowInteger::SetValue(std::string const& val) {
			*_data = (int)round(strtod(val.c_str(), NULL));
			//*Log << "If '" << val << "' = '" << _data <<
			//	"' ShadowInteger::SetValue worked correctly on " <<
			//	GetAbsolutePath() << std::endl;
		}
		
		std::string ShadowInteger::GetValueAsStdString() {
			std::stringstream ss;
			ss << *_data;
			return ss.str();
		}
		
		void ShadowInteger::Debug() {
		}
		
		int ShadowInteger::OperatorEqu(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == ShadowInteger::type) {
				*_data = ReadAtom(atm);
				retval = 0;
			}
			return retval;
		}
		
		int ShadowInteger::OperatorAdd(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == ShadowInteger::type) {
				int vali = ReadAtom(atm);
				*_data += vali;
				retval = 0;
			}
			return retval;
		}
		
		int ShadowInteger::OperatorSub(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == ShadowInteger::type) {
				int vali = ReadAtom(atm);
				*_data -= vali;
				retval = 0;
			}
			return retval;
		}

		int ShadowInteger::OperatorMul(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == ShadowInteger::type) {
				int vali = ReadAtom(atm);
				*_data *= vali;
				retval = 0;
			}
			return retval;
		}

		int ShadowInteger::OperatorDiv(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == ShadowInteger::type) {
				int vali = ReadAtom(atm);
				*_data = (int)(*_data / vali);
				retval = 0;
			}
			return retval;
		}

		int ShadowInteger::OperatorPow(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == ShadowInteger::type) {
				int vali = ReadAtom(atm);
				*_data = pow(*_data, vali);
				retval = 0;
			}
			return retval;
		}

		int ShadowInteger::_Procedure() {
			/*
			int retval = -1;
			return retval;
			*/
			
			*Log << GetAbsolutePath() << " = " << *_data << std::endl;
			return 0;
		}
		
		Atom* ShadowInteger::_Interpret(Atom* atm) {
			//*Log << "ShadowInteger::_Interpret: " << atm->identity << std::endl;
			/*
			if(atm->GetType() == ShadowInteger::type) return atm;
			else return new Notype(atm->identity);
			*/
			return new ShadowInteger(atm);
		}

		void* ShadowInteger::GetRawData() {
			return (void*)_data;
		}

		int ShadowInteger::ReadAtom(const Atom* atm) {
			char t = ((Atom*)atm)->GetType();
			if(t == Integer::type)
				return *(int*)((Integer*)atm)->GetRawData();
			else if(t == Float::type)
				return round(*(double*)((Float*)atm)->GetRawData());
			else if(t == String::type) {
				std::string str = ((String*)atm)->GetValueAsStdString();
				if(!ValidateStrtod(str)) throw std::invalid_argument("Could not convert String to ShadowInteger:  " + str);
				return round(strtod(str.c_str(), NULL));
			} else if(t == ShadowInteger::type) {
				return *((ShadowInteger*)atm)->_data;
			} else if(t == Notype::type) {
				if(!ValidateStrtod(atm->identity)) throw std::invalid_argument("Could not convert Literal to ShadowInteger:  " + atm->identity);
				*Log << "debug:  Notype > ShadowInteger:  " << atm->identity << std::endl;
				return (int)strtod(atm->identity.c_str(), NULL);
			}
			else return 0;
		}

	}
	
}
