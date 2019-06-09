/*
 *  TestMachine.cpp
 *  Test
 *
 *  Created by james on 2/16/19.
 *  Copyright 2019 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "TestMachine.h"
#include "Float.h"
#include "String.h"
#include "Notype.h"
#include "StringStuff.h"

namespace jmb {

	namespace common {
		
		const char TestMachine::type = 0x04;
		
		TestMachine::TestMachine() {
			TestMachine("");
		}
		
		TestMachine::TestMachine(std::string const& name) : Atom(name){
			_type = TestMachine::type;
			_Init();
			//_data = 0;
		}

		TestMachine::TestMachine(const Atom* atm) /*: Atom(atm)*/ {
			assert(0); // i see no reason why this should happen
			TestMachine(atm->identity);
			_type = TestMachine::type;
			isEphemeral = true;
			containsValidData = true;
			char t = ((Atom*)atm)->GetType();
			if(t == TestMachine::type /*|| t == Float::type
				|| t == String::type*/ || Notype::type) {
				try {
					//_data = ReadAtom(atm);
				} catch (std::invalid_argument& e) {
					std::cout << "ERROR:  " << e.what() << std::endl;
					containsValidData = false;
				}
			} //else assert(t == TestMachine::type);
			else _type = Notype::type;
		}
		
		TestMachine::~TestMachine() {
		}

		int TestMachine::Command(std::string const& cmd) {
			if(cmd == "clear") {
				//_data = 0;
				return -1;
			} else return Atom::Command(cmd);
		}

		void TestMachine::SetValue(std::string const& val) {
			//_data = (int)round(strtod(val.c_str(), NULL));
			
			//std::cout << "If '" << val << "' = '" << _data <<
			//	"' TestMachine::SetValue worked correctly on " <<
			//	GetAbsolutePath() << std::endl;
		}
		
		std::string TestMachine::GetValueAsStdString() {
			std::stringstream val;
			val << "TestMachine@" << std::hex << (unsigned long long int)GetRawData();
			std::string retval = val.str();
			//char tmpc[128] = {};
			//snprintf(tmpc, 128, "%d", _data);
			//retval += tmpc;
			return retval;
		}
		
		void TestMachine::Debug() {
		}

		/*		
		int TestMachine::OperatorEqu(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == TestMachine::type) {
				_data = ReadAtom(atm);
			}
			return retval;
		}
		
		int TestMachine::OperatorAdd(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == TestMachine::type) {
				int vali = ReadAtom(atm);
				_data += vali;
				retval = 0;
			}
			return retval;
		}
		
		int TestMachine::OperatorSub(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == TestMachine::type) {
				int vali = ReadAtom(atm);
				_data -= vali;
				retval = 0;
			}
			return retval;
		}

		int TestMachine::OperatorMul(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == TestMachine::type) {
				int vali = ReadAtom(atm);
				_data *= vali;
				retval = 0;
			}
			return retval;
		}

		int TestMachine::OperatorDiv(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == TestMachine::type) {
				int vali = ReadAtom(atm);
				_data = (int)(_data / vali);
				retval = 0;
			}
			return retval;
		}

		int TestMachine::OperatorPow(Atom* atm) {
			int retval = -1;
			if(atm->GetType() == TestMachine::type) {
				int vali = ReadAtom(atm);
				_data = pow(_data, vali);
				retval = 0;
			}
			return retval;
		}
		*/

		int TestMachine::_Procedure() {
			int retval = -1;
			retval = 0;
			return retval;
		}
		
		Atom* TestMachine::_Interpret(Atom* atm) {
			//std::cout << "TestMachine::_Interpret: " << atm->identity << std::endl;
			/*
			if(atm->GetType() == TestMachine::type) return atm;
			else return new Notype(atm->identity);
			*/
			return new TestMachine(atm);
		}

		void* TestMachine::GetRawData() {
			return (void*)this; //(void*)&_data;
		}

		void* TestMachine::ReadAtom(const Atom* atm) {
			/*
			char t = ((Atom*)atm)->GetType();
			if(t == TestMachine::type)
				return *(int*)((TestMachine*)atm)->GetRawData();
			else if(t == Float::type)
				return round(*(double*)((Float*)atm)->GetRawData());
			else if(t == String::type) {
				std::string str = ((String*)atm)->GetValueAsStdString();
				if(!ValidateStrtod(str)) throw std::invalid_argument("Could not convert String to TestMachine:  " + str);
				return round(strtod(str.c_str(), NULL));
			} else if(t == Notype::type) {
				if(!ValidateStrtod(atm->identity)) throw std::invalid_argument("Could not convert Literal to TestMachine:  " + atm->identity);
				return (int)strtod(atm->identity.c_str(), NULL);
			}
			else */ return NULL;
		}

		void TestMachine::_Init() {
			_Window = _Renderer = _Buffer = NULL;
			int ok = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
			if(ok != 0) {
				// error condition...
				std::cout << "ERROR:  Could not initialize SDL:  " << SDL_GetError() <<std::endl;
			} else {
				std::string id = identity + " (" + GetValueAsStdString() + ")";
				_Window = (void*)SDL_CreateWindow(id.c_str(), 0, 0, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
				_Renderer = (void*)SDL_CreateRenderer((SDL_Window*)_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
				assert(_Window != NULL);
				assert(_Renderer != NULL);
				TTF_Init();
			}
		}
	}
	
}
