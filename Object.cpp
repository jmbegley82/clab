/*
 *  Object.cpp
 *  Test
 *
 *  Created by james on 7/7/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include "Object.h"
#include "StrSplit.h"

namespace jmb {
	
	namespace common {
		
		const char Object::type = 0x00;
		
		Object::Object() {
			Object("");
		}
		
		Object::Object(std::string const& name) {
			identity = name;
			owner = NULL;
			_ownedObjectCount = 0;
			for(int i=0; i<MAXOBJS; i++) {
				_ownedObjects[i] = NULL;
			}
			_data = NULL;
			_type = type;
			mapThrough = true;
		}
		
		Object::~Object() {
			_Purge();
		}
		
		Object* Object::Dereference(std::string const& name) {
			// ex. ""
			if(name == "") return this;
			
			if(!mapThrough) {
				// attempting to reach through this object,
				//  but it isn't one that supports owned objects
				std::cout << std::endl << "BLOCK" << std::endl;
				return NULL;
			}
			
			CommandSplit CSSlash(name, "/");
			if(CSSlash.left == "" && CSSlash.right == "") {
				// ex. "Atom"
				return _GetOwnedObject(name);
			} else {
				// ex. "Atom/terra/pos/X"
				Object* obj = _GetOwnedObject(CSSlash.left);
				if(obj == NULL) return NULL;
				else return obj->Dereference(CSSlash.right);
			}
		}
		
		void Object::AddOwnedObject(Object* obj) {
			// todo: check for existing name!
			if(!mapThrough) return; // don't create objects you can't address!
			if(_ownedObjectCount < MAXOBJS && _GetOwnedObject(obj->identity) == NULL) {
				if(obj->owner != NULL) {
					obj->LeaveOwner();
				}
				obj->owner = this;
				_ownedObjects[_ownedObjectCount] = obj;
				_ownedObjectCount++;
			}
		}
		
		void Object::DelOwnedObject(std::string const& name) {
			// todo: everything
			if(!mapThrough) return; // should be empty
			int idx = _GetOwnedObjectIndex(name);
			if(idx < MAXOBJS) {
				_DeleteByIndex(idx);
				_MakeContiguous();
			}
		}
		
		void Object::GiveAway(Object* obj) {
			if(!mapThrough) return; // nothing to give away
			int idx = _GetOwnedObjectIndex(obj);
			if(idx < MAXOBJS) {
				_ownedObjects[idx] = NULL;
				_MakeContiguous();
			}
		}
		
		void Object::LeaveOwner() {
			if(owner != NULL) {
				owner->GiveAway(this);
				owner = NULL;
			}
		}
		
		int Object::Command(std::string const& cmd) {
			if(cmd == "") {
				return _Procedure();
			}
			
			Sentence sent(cmd);
			if(sent.op == "") {
				// cmd is a path to a procedure
				Object* obj = Dereference(cmd);
				if(obj != NULL) {
					obj->Command("");
					return 0;
				}
				return -1;
			}
			Object* subject = Dereference(sent.subject);
			if(subject != NULL) {
				if(sent.target[0] == '\'' && sent.target[sent.target.length()-1] == '\'') {
					// don't  dereference a target within single quotes,
					// just pass the enclosed text to subject->Command
					std::string fixedTarget = sent.target.substr(1, sent.target.length()-2);
					return subject->Command(sent.op + fixedTarget);
				}
				Object* target = Dereference(sent.target);
				if(target != NULL) {
					if(sent.op == "=") {
						return subject->OperatorEqu(target);
					} else if(sent.op == "+=") {
						return subject->OperatorAdd(target);
					} else if(sent.op == "-=") {
						return subject->OperatorSub(target);
					} else if(sent.op == "*=") {
						return subject->OperatorMul(target);
					} else if(sent.op == "/=") {
						return subject->OperatorDiv(target);
					} else if(sent.op == "^=") {
						return subject->OperatorPow(target);
					}
				} else {
					// could not dereference target; pass as command
					return subject->Command(sent.op + sent.target);
				}
			}
			
			return -1;
		}
		
		void Object::Tick(unsigned int ms) {
			for(int i=0; i<_ownedObjectCount; i++) {
				_ownedObjects[i]->Tick(ms);
			}
		}
		
		void* Object::GetValue() {
			return _data;
		}
		
		void Object::SetValue(void* val) {
			_data = val;
		}
		
		char Object::GetType() {
			return _type;
		}
		
		void Object::_MakeContiguous() {
			// makes _ownedObjects array contiguous and sets _ownedObjectCount
			_ownedObjectCount = 0;
			for(int i=0; i < MAXOBJS; i++) {
				if(_ownedObjects[i] != NULL) {
					_ownedObjects[_ownedObjectCount] = _ownedObjects[i];
					_ownedObjectCount++;
				}
			}
		}
		
		void Object::Debug() {
			_MakeContiguous();
			std::cout << "Debug(): " << __FILE__ << " at " << __LINE__ << " identity=" <<
			identity << "\n";
			std::cout << "Debug(): Owned objects:";
			for(int i=0; i<_ownedObjectCount; i++) {
				std::cout << " " << _ownedObjects[i]->identity;
			}
			std::cout << "\n";
			for(int i=0; i<_ownedObjectCount; i++) {
				_ownedObjects[i]->Debug();
			}
		}
		
		unsigned int Object::_GetOwnedObjectIndex(std::string const& name) {
			// return MAXOBJS if not found
			unsigned int retval;
			for(retval=0; retval<MAXOBJS; retval++) {
				if(_ownedObjects[retval] != NULL &&
				   _ownedObjects[retval]->identity == name) {
					break;
				}
			}
			return retval;
		}
		
		unsigned int Object::_GetOwnedObjectIndex(Object* obj) {
			unsigned int retval;
			for(retval=0; retval<MAXOBJS; retval++) {
				if(_ownedObjects[retval] == obj) {
					break;
				}
			}
			return retval;
		}
		
		Object* Object::_GetOwnedObject(std::string const& name) {
			// should only get a one-name path
			// no slashes and definitely no operators!
			Object* retval = NULL;
			int idx = _GetOwnedObjectIndex(name);
			if(idx < MAXOBJS) retval = _ownedObjects[idx];
			return retval;
		}
		
		void Object::_DeleteByIndex(unsigned int idx) {
			// unsafe!  assumes all critical checks have been performed
			//if(idx < MAXOBJS) {
			//if(_ownedObjects[idx] != NULL)
			delete _ownedObjects[idx];
			_ownedObjects[idx] = NULL;
			//}
		}
		
		std::string Object::_GetPath() {
			std::string retval = identity;
			Object* nextUp = owner;
			while(nextUp != NULL) {
				retval = nextUp->identity + "/" + retval;
				nextUp = nextUp->owner;
			}
			return retval;
		}
		
		void Object::_Purge() {
			// this should be more thorough?
			_MakeContiguous();
			for(int i=0; i<_ownedObjectCount; i++) {
				_DeleteByIndex(i);
			}
		}
		
		int Object::_Procedure() {
			std::cout << _GetPath() << " Stub.\n";
			return 0;
		}
		
		int Object::OperatorEqu(Object* obj) {
			std::cout << __FUNCTION__ << " Stub.\n";
			return 0;
		}
		
		int Object::OperatorAdd(Object* obj) {
			std::cout << __FUNCTION__ << " Stub.\n";
			return 0;
		}
		
		int Object::OperatorSub(Object* obj) {
			std::cout << __FUNCTION__ << " Stub.\n";
			return 0;
		}
		
		int Object::OperatorMul(Object* obj) {
			std::cout << __FUNCTION__ << " Stub.\n";
			return 0;
		}
		
		int Object::OperatorDiv(Object* obj) {
			std::cout << __FUNCTION__ << " Stub.\n";
			return 0;
		}
		
		int Object::OperatorPow(Object* obj) {
			std::cout << __FUNCTION__ << " Stub.\n";
			return 0;
		}
		
	}
	
}