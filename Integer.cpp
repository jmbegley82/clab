/*
 *  Integer.cpp
 *  Test
 *
 *  Created by james on 7/8/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include <cmath>
#include <assert.h>
#include "Integer.h"
#include "Float.h"
#include "String.h"
#include "StrSplit.h"

namespace jmb {

	namespace common {
		
		const char Integer::type = 0x01;
		
		Integer::Integer() : Object() {
		}
		
		Integer::Integer(std::string const& name) : Object(name) {
			_type = type;
		}
		
		Integer::~Integer() {
			_Purge();
		}
		
		int Integer::Command(std::string const& cmd) {
			Sentence sent(cmd);
			if (sent.subject == "") {
				if(sent.op == "=") {
					_data = (void*)(int)strtod(sent.target.c_str(), NULL);
				} else {
					assert(0); // do all other operators
				}
				return 0;
			}
			return -1; //Object::Command(cmd);
		}
		
		void Integer::Tick(unsigned int ms) {
			Object::Tick(ms);
		}
		
		void Integer::Debug() {
			Object::Debug();
		}
		
		int Integer::_Procedure() {
			return Object::_Procedure();
		}
		
		int Integer::_Interpret(Object* obj) {
			int retval = 0;
			char t = obj->GetType();
			if(t == String::type) {
				// String handler
				std::string* str = static_cast<std::string*>(obj->GetValue());
				retval = strtod((*str).c_str(), NULL);
			} else if(t == Float::type) {
				double* dub = static_cast<double*>(obj->GetValue());
				retval = round(*dub);
			} else {
				// default handler
				retval = (int)obj->GetValue();
			}
			return retval;
		}
		
		int Integer::OperatorEqu(Object* obj) {
			_data = (void*)_Interpret(obj); //obj->GetValue();
			return 0;
		}
		
		int Integer::OperatorAdd(Object* obj) {
			//return Object::_OperatorAdd(obj);
			_data = (void*)((int)_data + _Interpret(obj));
			return 0;
		}
		
		int Integer::OperatorSub(Object* obj) {
			//return Object::_OperatorSub(obj);
			_data = (void*)((int)_data - _Interpret(obj));
			return 0;
		}
		
		int Integer::OperatorMul(Object* obj) {
			//return Object::_OperatorMul(obj);
			_data = (void*)((int)_data * _Interpret(obj));
			return 0;
		}
		
		int Integer::OperatorDiv(Object* obj) {
			//return Object::_OperatorDiv(obj);
			_data = (void*)((int)_data / _Interpret(obj));
			return 0;
		}
		
		int Integer::OperatorPow(Object* obj) {
			//return Object::_OperatorPow(obj);
			_data = (void*)(int)(double)pow((double)(int)_data, (double)_Interpret(obj));
			return 0;
		}
		
	}

}