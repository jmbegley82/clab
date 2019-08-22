/*
 *  Node.cpp
 *  Test
 *
 *  Created by james on 7/14/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <map>
#include <cassert>
#include "Log.h"
#include "Types.h"
#include "StringManip.h"
#include "Node.h"
#include "Integer.h"
#include "Float.h"
#include "String.h"
#include "Notype.h"

namespace jmb {
	
	namespace common {
		
		const char Node::type = 0x11;
		
		Node::Node() {
			Node("");
		}
		
		Node::Node(std::string const& name) : NodeBase(name) {
			_mapThrough = true;
			_type = type;
		}

		Node::Node(const Atom* atm) : NodeBase(atm) {
			Node(atm->identity);
			isEphemeral = true;
			char t = ((Atom*)atm)->GetType();
			if(t == Node::type) {
				// only valid conversion is Node to (Atom*)Node
				Node* nod = (Node*)atm;
				for(AtomMapItr i = nod->_children.begin(); i != nod->_children.end(); i++) {
					_children[i->first] = i->second;
				}
			}// else assert(t == Node::type);
		}
		
		Node::~Node() {
			//*Log << "Node::~Atom" << std::endl;
			if(!isEphemeral) _Purge();
		}

		Atom* Node::CtorWrapper(std::string name) {
			return new Node(name);
		}

		int Node::AddChild(Atom* atm) {
			if(_GetChild(atm->identity) != NULL)
				return -2; // name exists within this node
			if(atm->parent != NULL) {
				atm->LeaveParent();
			}
			atm->parent = this;
			_children[atm->identity] = atm;
			return 0;
		}
		
		int Node::DelChild(Atom* atm) {
			AtomMapItr target = _GetChildItr(atm);
			if(target == _children.end()) return -1;  // not found
			_DeleteByItr(target);
			return 0;
		}
		
		int Node::DelChild(std::string const& name) {
			AtomMapItr target = _GetChildItr(name);
			if(target == _children.end()) return -1;  // not found
			_DeleteByItr(target);
			return 0;
		}
		
		int Node::FreeChild(Atom* atm) {
			AtomMapItr target = _GetChildItr(atm);
			if(target == _children.end()) return -1;  // not found
			_children.erase(target);
			return 0;
		}
		
		int Node::OperatorEqu(Atom* atm) {
			*Log << "Node::" << __FUNCTION__ << ": stub: " << atm->identity << std::endl;
			return 0; //NI
		}
		
		int Node::_Procedure() {
			Atom::_Procedure();
			for(AtomMapItr i = _children.begin(); i != _children.end(); i++) {
				i->second->Command("");
			}
			return 0;
		}

		Atom* Node::_Interpret(Atom* atm) {
			//*Log << "Node::_Interpret" << std::endl;
			return new Node(atm);
		}

		Atom* Node::_GetChild(std::string const& name) {
			// should only get a one-name path
			// no slashes and definitely no operators!
			Atom* retval = NULL;
			AtomMapItr i = _GetChildItr(name);
			if(i != _children.end()) retval = i->second;
			return retval;
		}

		AtomMapItr Node::_GetChildItr(std::string const& name) {
			return _children.find(name);
		}

		AtomMapItr Node::_GetChildItr(Atom* atm) {
			AtomMapItr retval = _children.begin();
			while(retval != _children.end()) {
				if(retval->second == atm) return retval;
				retval++;
			}
			return retval;
		}

		void Node::_DeleteByItr(AtomMapItr target) {
			// unsafe!  assumes all critical checks have been performed!
			Atom* atm = target->second;
			_children.erase(target);
			delete atm;
		}

		void Node::_Purge() {
			// this should be more thorough?
			for(AtomMapItr i = _children.begin(), next_i = i; i!= _children.end(); i = next_i) {
				++next_i;
				_DeleteByItr(i);
			}
		}

		void Node::Tick(int time) {
			for(AtomMapItr i = _children.begin(); i != _children.end(); i++) {
				i->second->Tick(time);
				if(i->second->wasUpdated)
					*Log << "We got a live one!  "  << i->second->identity << std::endl;
				i->second->wasUpdated = false;
				if(i->second->wasUpdated) {
					*Log << "What the shit?  This should never be reached..." << std::endl;
				}
			}
		}

	}
}
