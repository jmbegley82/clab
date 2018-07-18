/*
 *  Atom.cpp
 *  Test
 *
 *  Created by james on 7/13/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <assert.h>
#include "Atom.h"
#include "Node.h"
#include "StrSplit.h"

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
					root = (Atom*)root->parent;
				}
				// pass noSlash to the root
				return root->Dereference(noSlash);
			} else return NULL;
		}

		
		int Atom::Command(std::string const& cmd) {
			if(cmd == "") return _Procedure();
			Sentence s(cmd);
			Atom* sub = Dereference(s.subject);
			if(sub == NULL) return -1;
			if(sub == this) {
				if(s.op == "=") return OperatorEqu(Dereference(s.target));
				if(s.op == "+=") return OperatorAdd(Dereference(s.target));
				if(s.op == "-=") return OperatorSub(Dereference(s.target));
				if(s.op == "*=") return OperatorMul(Dereference(s.target));
				if(s.op == "/=") return OperatorDiv(Dereference(s.target));
				if(s.op == "^=") return OperatorPow(Dereference(s.target));
				return -1;
			}
			
			return sub->Command(s.op + s.target);
			//else return -1;
		}
		
		std::string Atom::GetValueAsStdString() {
			std::string retval = "";
			return retval;
		}
		
		std::string Atom::GetAbsolutePath() {
			std::string retval = "";
			Atom* root = GetRoot();
			if(root != this) {
				retval = identity;
				Atom* nextUp = (Atom*)parent;
				while(nextUp != NULL) {
					retval = nextUp->identity + "/" + retval;
					nextUp = (Atom*)nextUp->parent;
				}
				CommandSplit CSSlash(retval, "/");
				if(CSSlash.left != "")
					retval = CSSlash.right;
				retval = "/" + retval;
			}
			return retval;
		}
		
		void Atom::Debug() {}
		
		void Atom::SetValue(std::string const& val) {}
		
		char Atom::GetType() {
			return _type;
		}
		
		void Atom::LeaveParent() {
			if(parent != NULL) {
				parent->FreeChild(this);
				parent = NULL;
			}
		}
		
		int Atom::OperatorEqu(Atom* atm) {
			std::cout << "Atom::" << __FUNCTION__ << ": stub" << std::endl;
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
		
		Atom* Atom::GetRoot() {
			Atom* retval = (Atom*)parent;
			if(retval == NULL) return this;
			while(retval->parent != NULL) {
				retval = (Atom*)retval->parent;
			}
			return retval;
		}
		
		int Atom::_Procedure() {
			std::cout << GetAbsolutePath() << std::endl;
			return 0;
		}
		
	}

}