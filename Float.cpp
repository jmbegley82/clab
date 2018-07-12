/*
 *  Float.cpp
 *  Test
 *
 *  Created by james on 7/12/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include <cmath>
#include <assert.h>
#include "Object.h"
#include "Float.h"
#include "Integer.h"
#include "String.h"
#include "StrSplit.h"

namespace jmb {
	
	namespace common {
		
		const char Float::type = 0x03;
		
		Float::Float() : Object() {
		}
		
		Float::Float(std::string const& name) : Object(name) {
			_type = type;
			_data = static_cast<double*>(new double);
		}
		
		Float::~Float() {
			_Purge();
			delete static_cast<double*>(_data);
		}
		
		int Float::Command(std::string const& cmd) {
			Sentence sent(cmd);
			if (sent.subject == "") {
				if(sent.op == "=") {
					double* dub = static_cast<double*>(_data);
					*dub = strtod(sent.target.c_str(), NULL);
				} else {
					assert(0); // do all other operators
				}
				return 0;
			}
			return -1; //Object::Command(cmd);
		}
		
		void Float::Tick(unsigned int ms) {
			Object::Tick(ms);
		}
		
		void Float::Debug() {
			Object::Debug();
		}
		
		int Float::_Procedure() {
			return Object::_Procedure();
		}
		
		double Float::_Interpret(Object* obj) {
			double retval = 0;
			char t = obj->GetType();
			if(t == String::type) {
				// String handler
				std::string* str = static_cast<std::string*>(obj->GetValue());
				retval = strtod((*str).c_str(), NULL);
			} else if(t == Integer::type) {
				retval = (double)(int)obj->GetValue();
			} else {
				// default handler
				double* dub = static_cast<double*>(obj->GetValue());
				retval = *dub;
			}
			return retval;
		}
		
		int Float::OperatorEqu(Object* obj) {
			double* dub = static_cast<double*>(_data);
			*dub = _Interpret(obj); //obj->GetValue();
			return 0;
		}
		
		int Float::OperatorAdd(Object* obj) {
			double* dub = static_cast<double*>(_data);
			*dub = *dub + _Interpret(obj);
			return 0;
		}
		
		int Float::OperatorSub(Object* obj) {
			double* dub = static_cast<double*>(_data);
			*dub = *dub - _Interpret(obj);
			return 0;
		}
		
		int Float::OperatorMul(Object* obj) {
			double* dub = static_cast<double*>(_data);
			*dub = *dub * _Interpret(obj);
			return 0;
		}
		
		int Float::OperatorDiv(Object* obj) {
			double* dub = static_cast<double*>(_data);
			*dub = *dub / _Interpret(obj);
			return 0;
		}
		
		int Float::OperatorPow(Object* obj) {
			double* dub = static_cast<double*>(_data);
			*dub = pow(*dub, _Interpret(obj));
			return 0;
		}
		
	}
	
}