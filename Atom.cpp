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
#include "Notype.h"
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
			// Applied to command string subjects and targets to convert them
			//   into Atom*s
			
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
			} else //return NULL;
			{
				return new Notype(name);  // is it wise to put that into identity?
			}
		}

		
		int Atom::Command(std::string const& cmd) {
			// Splits cmd into subject, op(erator), and target, Dereferences subject,
			//   sends op + target to it; given one addressed to us, Dereference target and
			//   send it to the appropriate Operator function
			
			if(cmd == "") return _Procedure();
			Sentence s(cmd);
			Atom* sub = Dereference(s.subject);
			if(sub == NULL) return -1;
			if(sub->GetType() == Notype::type) {
				assert(0);
			}
			/*
			if(sub == this) {
				Atom* atm = _Interpret(Dereference(s.target));
				if(s.op == "=") return OperatorEqu(atm); //Dereference(s.target));
				if(s.op == "+=") return OperatorAdd(atm); //Dereference(s.target));
				if(s.op == "-=") return OperatorSub(atm); //Dereference(s.target));
				if(s.op == "*=") return OperatorMul(atm); //Dereference(s.target));
				if(s.op == "/=") return OperatorDiv(atm); //Dereference(s.target));
				if(s.op == "^=") return OperatorPow(atm); //Dereference(s.target));
				return -1;
			}
			 */
			//return sub->Command(s.op + s.target);
			return sub->Command(s.op, Dereference(s.target));
		}
		
		int Atom::Command(std::string const& op, Atom* target) {
			Atom* trg = _Interpret(target);
			if(op == "") return _Procedure();
			if(op == "=") return OperatorEqu(trg);
			if(op == "+=") return OperatorAdd(trg);
			if(op == "-=") return OperatorSub(trg);
			if(op == "*=") return OperatorMul(trg);
			if(op == "/=") return OperatorDiv(trg);
			if(op == "^=") return OperatorPow(trg);
			if(trg->GetType() == Notype::type) delete trg;
			return -1;
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
		
		Atom* Atom::_Interpret(Atom* atm) {
			// default
			return atm;
		}
		
	}

}