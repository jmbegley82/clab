/*
 *  Atom.cpp
 *  Test
 *
 *  Created by james on 7/13/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include "Atom.h"

namespace jmb {

	namespace common {
		
		const char Atom::type = 0xFF;
		
		Atom::Atom() {
			Atom("");
		}
		
		Atom::Atom(std::string const& name) {
			identity = name;
			parent = NULL;
			_type = type;
		}
		
		Atom::~Atom() {
		}
		
		Atom* Atom::Dereference(std::string const& name) {
			if(name == "") return this;
			else if(name[0] == '/') {
				// remove the leading slash
				std::string noSlash = name;
				noSlash.erase(0, 1);
				// get top level Atom
				Atom* root = this;
				while(root->parent != NULL) {
					root = root->parent;
				}
				// pass noSlash to the root
				return root->Dereference(noSlash);
			} else return NULL;
		}

		
		int Atom::Command(std::string const& cmd) {
			if(cmd == "") return _Procedure();
			else return -1;
		}
		
		std::string Atom::GetValueAsStdString() {
			std::string retval = "";
			return retval;
		}
		
		void Atom::Debug() {}
		
		void Atom::SetValue(std::string const& val) {}
		
		char Atom::GetType() {
			return _type;
		}
		
		int Atom::OperatorEqu(Atom* atm) {
			return -1;
		}
		
		int Atom::OperatorAdd(Atom* atm) {
			return -1;
		}
		
		int Atom::OperatorSub(Atom* atm) {
			return -1;
		}
		
		int Atom::OperatorMul(Atom* atm) {
			return -1;
		}
		
		int Atom::OperatorDiv(Atom* atm) {
			return -1;
		}
		
		int Atom::OperatorPow(Atom* atm) {
			return -1;
		}
		
		std::string Atom::GetPath() {
			std::string retval = identity;
			Atom* nextUp = parent;
			while(nextUp != NULL) {
				retval = nextUp->identity + "/" + retval;
				nextUp = nextUp->parent;
			}
			retval = "/" + retval;
			return retval;
		}
		
		int Atom::_Procedure() {
			return -1;
		}
		
	}

}