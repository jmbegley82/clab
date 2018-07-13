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
			_data = static_cast<void*>(new int);
			_type = type;
			mapThrough = false;
		}
		
		Integer::~Integer() {
			_Purge();
			delete static_cast<int*>(_data);
		}
		
		int Integer::Command(std::string const& cmd) {
			if(cmd == "") {
				_Procedure();
				return 0;
			}
			Sentence sent(cmd);
			if (sent.subject == "") {
				if(sent.op == "=") {
					//int* data = static_cast<int*>(_data);
					//*data = (int)strtod(sent.target.c_str(), NULL);
					SetValue(sent.target);
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
		
		std::string Integer::GetValueAsStdString() {
			char out[32] = "";
			sprintf(out, "%d", _Interpret(this));
			return std::string(out);
			//return std::string(_Interpret(this));
		}
		
		void Integer::SetValue(std::string const& val) {
			int* data = static_cast<int*>(_data);
			*data = (int)strtod(val.c_str(), NULL);
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
				int* data = static_cast<int*>(obj->GetValue());
				retval = *data;
				//retval = (int)obj->GetValue();
			}
			return retval;
		}
		
		int Integer::OperatorEqu(Object* obj) {
			//_data = (void*)_Interpret(obj); //obj->GetValue();
			int* data = static_cast<int*>(_data);
			*data = _Interpret(obj);
			return 0;
		}
		
		int Integer::OperatorAdd(Object* obj) {
			//return Object::_OperatorAdd(obj);
			//_data = (void*)((int)_data + _Interpret(obj));
			int* data = static_cast<int*>(_data);
			*data = *data + _Interpret(obj);
			return 0;
		}
		
		int Integer::OperatorSub(Object* obj) {
			//return Object::_OperatorSub(obj);
			//_data = (void*)((int)_data - _Interpret(obj));
			int* data = static_cast<int*>(_data);
			*data = *data - _Interpret(obj);
			return 0;
		}
		
		int Integer::OperatorMul(Object* obj) {
			//return Object::_OperatorMul(obj);
			//_data = (void*)((int)_data * _Interpret(obj));
			int* data = static_cast<int*>(_data);
			*data = *data * _Interpret(obj);
			return 0;
		}
		
		int Integer::OperatorDiv(Object* obj) {
			//return Object::_OperatorDiv(obj);
			//_data = (void*)((int)_data / _Interpret(obj));
			int* data = static_cast<int*>(_data);
			*data = *data / _Interpret(obj);
			return 0;
		}
		
		int Integer::OperatorPow(Object* obj) {
			//return Object::_OperatorPow(obj);
			//_data = (void*)(int)(double)pow((double)(int)_data, (double)_Interpret(obj));
			int* data = static_cast<int*>(_data);
			*data = (int)pow((double)*data, (double)_Interpret(obj));
			return 0;
		}
		
	}

}