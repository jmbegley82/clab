/*
 *  Atom.cpp
 *  Test
 *
 *  Created by james on 7/13/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <cassert>
#include "Log.h"
#include "Atom.h"
#include "Node.h"
#include "Notype.h"
#include "StringStuff.h"

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
			isEphemeral = false;
			containsValidData = true;
			wasUpdated = false;  // it just pops into existence
			eraseMe = false;
		}

		Atom::Atom(const Atom* atm) {
			// this is where we'll handle conversion from other types
			// well not so much here, but in the derived classes
			Atom(atm->identity);  // happens enough times already...
			isEphemeral = true;
			containsValidData = atm->containsValidData;
			wasUpdated = atm->wasUpdated;
			eraseMe = atm->eraseMe;
		}
		
		Atom::~Atom() {
			if(!isEphemeral) LeaveParent();
		}

		Atom* Atom::CtorWrapper(std::string name) {
			return new Atom(name);
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
			std::string declarator = RemovePadding(s.declarator);
			std::string target = RemovePadding(s.target);
			std::string subject = RemovePadding(s.subject);
			_Declarate(declarator, subject);
			Atom* sub = Dereference(subject);
			if(sub == NULL) return -1;
			assert(sub->GetType() != Notype::type);
			if(declarator != "" && s.op == "") return 0; // prevent running _Procedure during initialization
			return sub->Command(s.op, Dereference(target));
		}
		
		int Atom::Command(std::string const& op, Atom* target) {
			int retval = -1;
			if(op == "") retval = _Procedure();
			else if(op == ":=") {
				retval = Command(target->identity);
				//assert(target->isEphemeral); delete target;
			} else {
				Atom* trg = _Interpret(target);
				if(trg->containsValidData) {
					if(op == "=") retval = OperatorEqu(trg);
					else if(op == "+=") retval = OperatorAdd(trg);
					else if(op == "-=") retval = OperatorSub(trg);
					else if(op == "*=") retval = OperatorMul(trg);
					else if(op == "/=") retval = OperatorDiv(trg);
					else if(op == "^=") retval = OperatorPow(trg);
					//else if(op == ":=") retval = this->Command(trg->identity);
				}
				assert(trg->isEphemeral);
				delete trg;
			}
			if(retval != -1) wasUpdated = true;
			return retval;
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
			*Log << "Atom::" << __FUNCTION__ << ": stub" << std::endl;
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
			*Log << GetAbsolutePath() << std::endl;
			return 0;
		}

		int Atom::_Declarate(std::string const& declarator, std::string const& subject) {
			return -1;
		}
		
		Atom* Atom::_Interpret(Atom* atm) {
			// default
			//*Log << "Atom::_Interpret" << std::endl;
			return new Atom(atm);
		}
		
		void* Atom::GetRawData() {
			return NULL;
		}
		
		void Atom::Tick(int time) {
			// almost purely virtual
			//*Log << GetAbsolutePath() << "::Tick(" << time << ")" << std::endl;
		}
	}

}
