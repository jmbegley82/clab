/*
 *  String.cpp
 *  Test
 *
 *  Created by james on 7/10/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include <string>
#include <iostream>
#include <assert.h>
#include "StrSplit.h"
#include "String.h"
#include "Integer.h"
#include "Float.h"

namespace jmb {

	namespace common {
		
		const char String::type = 0x02;
		
		String::String() {
			String("");
		}
		
		String::String(std::string const& name) : Object(name) {
			_data = static_cast<void*>(new std::string(""));
			_type = type;
			mapThrough = false;
		}
		
		String::~String() {
			_Purge();
			delete static_cast<std::string*>(_data);
		}
		
		int String::Command(std::string const& cmd) {
			if(cmd == "") {
				_Procedure();
				return 0;
			}
			Sentence sent(cmd);
			if(sent.subject == "") {
				// it's for us
				if(sent.op == "=") {
					//
					std::string* str = static_cast<std::string*>(_data);
					*str = sent.target;
					return 0;
				} else if(sent.op == "+=") {
					//
					assert(0);
					return 0;
				}
			}
			return Object::Command(cmd);
		}
		
		void String::Tick(unsigned int ms) {
			Object::Tick(ms);
		}
		
		void String::Debug() {
			Object::Debug();
		}
		
		int String::_Procedure() {
			return Object::_Procedure();
		}
		
		std::string String::_Interpret(Object* obj) {
			std::string retval = "";
			char t = obj->GetType();
			if(t == Integer::type) {
				// Integer handler
				char buf[32] = "";
				int* in = static_cast<int*>(obj->GetValue());
				sprintf(buf, "%d", *in);
				retval = std::string(buf);
			} else if(t == Float::type) {
				char buf[32] = "";
				double* dub = static_cast<double*>(obj->GetValue());
				sprintf(buf, "%f", *dub);
				retval = std::string(buf);
			} else {
				// default handler
				retval = *(static_cast<std::string*>(obj->GetValue()));
			}
			return retval;
		}
		
		int String::OperatorEqu(Object* obj) {
			std::string *str = static_cast<std::string*>(_data);
			(*str) = _Interpret(obj);
			return 0;
		}
		
		int String::OperatorAdd(Object* obj) {
			std::string *str = static_cast<std::string*>(_data);
			(*str) += _Interpret(obj);
			return 0;
		}

	}

}