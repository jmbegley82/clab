/*
 *  String.cpp
 *  Test
 *
 *  Created by james on 2/3/19.
 *  Copyright 2019 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "String.h"
#include "Float.h"
#include "Notype.h"

namespace jmb {

	namespace common {
		
		const char String::type = 0x03;
		
		String::String() {
			String("");
		}
		
		String::String(std::string const& name) : Atom(name){
			_type = String::type;
			_data = "";
		}

		String::String(const Atom* atm) /*: Atom(atm)*/ {
			String(atm->identity);
			_type = String::type;
			isEphemeral = true;
			char t = ((Atom*)atm)->GetType();
			if(t == String::type) {
				_data = ReadAtom(atm);
			} //else assert(t == String::type);
			else _type = Notype::type;
		}
		
		String::~String() {
		}
		
		void String::SetValue(std::string const& val) {
			_data = val;
			//std::cout << "If '" << val << "' = '" << _data <<
			//	"' String::SetValue worked correctly on " <<
			//	GetAbsolutePath() << std::endl;
		}
		
		std::string String::GetValueAsStdString() {
			return _data;
		}
		
		void String::Debug() {
		}
		
		int String::OperatorEqu(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == String::type) {
				_data = ReadAtom(atm);
			}
			return retval;
		}
		
		int String::OperatorAdd(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == String::type) {
				std::string vals = ReadAtom(atm);
				_data += vals;
				retval = 0;
			}
			return retval;
		}

		int String::_Procedure() {
			int retval = -1;
			return retval;
		}
		
		Atom* String::_Interpret(Atom* atm) {
			//std::cout << "String::_Interpret: " << atm->identity << std::endl;
			/*
			if(atm->GetType() == String::type) return atm;
			else return new Notype(atm->identity);
			*/
			return new String(atm);
		}

		void* String::GetRawData() {
			return (void*)&_data;
		}

		std::string String::ReadAtom(const Atom* atm) {
			char t = ((Atom*)atm)->GetType();
			if(t == String::type)
				return (*(std::string*)((String*)atm)->GetRawData());
			else return 0;
		}
	}
	
}