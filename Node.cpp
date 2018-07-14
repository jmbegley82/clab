/*
 *  Node.cpp
 *  Test
 *
 *  Created by james on 7/14/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include "Node.h"

namespace jmb {

	namespace common {

		const char Node::type = 0x01;
		
		Atom* Node::Dereference(std::string const& name) {
			Atom* retval = Atom::Dereference(name);  // checks if it's us
			if(retval == NULL) {
				for(int i=0; i<_childCount; i++) {
				}
			}
			return retval;
		}
		
		int Node::Command(std::string const& cmd) {
			return -1;
		}
		
		unsigned int Node::_GetChildIndex(std::string const& name) {
			// return MAXOBJS if not found
			unsigned int retval;
			for(retval=0; retval<MAXOBJS; retval++) {
				if(_children[retval] != NULL &&
				   _children[retval]->identity == name) {
					break;
				}
			}
			return retval;
		}
		
		unsigned int Node::_GetChildIndex(Atom* atm) {
			unsigned int retval;
			for(retval=0; retval<MAXOBJS; retval++) {
				if(_children[retval] == atm) {
					break;
				}
			}
			return retval;
		}
		
		Atom* Node::_GetChild(std::string const& name) {
			// should only get a one-name path
			// no slashes and definitely no operators!
			Atom* retval = NULL;
			int idx = _GetChildIndex(name);
			if(idx < MAXOBJS) retval = _children[idx];
			return retval;
		}
		
		void Node::_DeleteByIndex(unsigned int idx) {
			// unsafe!  assumes all critical checks have been performed
			delete _children[idx];
			_children[idx] = NULL;
			//}
		}
		
		void Node::_MakeContiguous() {
			_childCount = 0;
			for(int i=0; i < MAXOBJS; i++) {
				if(_children[i] != NULL) {
					_children[_childCount] = _children[i];
					_childCount++;
				}
			}
		}
		
		void Node::_Purge() {
			// this should be more thorough?
			_MakeContiguous();
			for(int i=0; i<_childCount; i++) {
				_DeleteByIndex(i);
			}
		}
		
	}

}