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
		
		const char Node::type = 0x00;
		
		Node::Node() {
			Node("");
		}
		
		Node::Node(std::string const& name) : NodeBase(name) {
			/*
			for(int i=0; i<MAXOBJS; i++) {
				_children[i] = NULL;
			}
			_childCount = 0;
			*/
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
				/*
				for(int i=0; i<MAXOBJS; i++) {
					_children[i] = nod->_children[i];
				}
				*/
				//_children.insert(_children.begin(), nod->_children.begin(), nod->_children.end());
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
		
		Atom* Node::Dereference(std::string const& name) {
			Atom* retval = Atom::Dereference(name);  // checks if it's us; rules out name==""
			if(retval->GetType() == Notype::type) {
				delete retval;
				retval = NULL;
			}
			if(_mapThrough) {
				// in case we want to create a Node-derived object with private children
				if(retval == NULL) {
					std::string dname;
					if(name[0] == '/') {
						// absolute path
						dname = name.substr(1);
						retval = GetRoot()->Dereference(dname);
					} else {
						dname = name;
						CommandSplit CSSlash(dname, "/");
						if(CSSlash.left != "") {
							Atom* nextUp = _GetChild(CSSlash.left);
							if(nextUp != NULL) {
								retval = nextUp->Dereference(CSSlash.right);
							}
						} else {
							Atom* nextUp = _GetChild(dname);
							retval = nextUp;
						}
					}
				}
			}
			if(retval == NULL) retval = new Notype(name);
			return retval;
		}
		
		int Node::AddChild(Atom* atm) {
			/*
			if(_childCount >= MAXOBJS)
				return -1;  // we're full
			*/
			if(_GetChild(atm->identity) != NULL)
				return -2; // name exists within this node
			if(atm->parent != NULL) {
				atm->LeaveParent();
			}
			atm->parent = this;
			//_children[_childCount] = atm;
			//_childCount++;
			_children[atm->identity] = atm;
			return 0;
		}
		
		int Node::DelChild(Atom* atm) {
			/*
			int idx = _GetChildIndex(atm);
			if(idx == MAXOBJS) return -1;  // not found
			_DeleteByIndex(idx);
			*/
			AtomMapItr target = _GetChildItr(atm);
			if(target == _children.end()) return -1;  // not found
			_DeleteByItr(target);
			return 0;
		}
		
		int Node::DelChild(std::string const& name) {
			/*
			unsigned int idx = _GetChildIndex(name);
			if(idx == MAXOBJS) return -1; // not found
			_DeleteByIndex(idx);
			*/
			AtomMapItr target = _GetChildItr(name);
			if(target == _children.end()) return -1;  // not found
			_DeleteByItr(target);
			return 0;
		}
		
		int Node::FreeChild(Atom* atm) {
			/*
			int idx = _GetChildIndex(atm);
			if(idx == MAXOBJS) return -1; // not found
			_children[idx] = NULL;
			_MakeContiguous();
			*/
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
			/*
			for(int i=0; i<_childCount; i++) {
				_children[i]->Command("");
			}
			*/
			for(AtomMapItr i = _children.begin(); i != _children.end(); i++) {
				i->second->Command("");
			}

			return 0;
		}

		int Node::_Declarate(std::string const& declarator, std::string const& subject) {
			Atom* noob = NULL;
			/*
			if(declarator == "Node") {
				noob = new Node(subject);
			} else if(declarator == "Integer") {
				noob = new Integer(subject);
			} else if(declarator == "Float") {
				noob = new Float(subject);
			} else if(declarator == "String") {
				noob = new String(subject);
			} else if(declarator == "Video") {
				noob = new Video(subject);
			}
			*/

			noob = Types::CreateNew(declarator, subject);

			if(noob == NULL) {
				return -3; // invalid declarator
			}
			//else {
				//if(AddChild(noob) != 0) return -2; // already exists or overflow
			return AddChild(noob);
				
			//}
			//return 0;
		}
		
		Atom* Node::_Interpret(Atom* atm) {
			//*Log << "Node::_Interpret" << std::endl;
			//return Atom::_Interpret(atm);
			return new Node(atm);
		}

/*	
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
*/

		Atom* Node::_GetChild(std::string const& name) {
			// should only get a one-name path
			// no slashes and definitely no operators!
			Atom* retval = NULL;
			/*
			int idx = _GetChildIndex(name);
			if(idx < MAXOBJS) retval = _children[idx];
			*/
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

/*		
		void Node::_DeleteByIndex(unsigned int idx) {
			// unsafe!  assumes all critical checks have been performed
			delete _children[idx];
			_children[idx] = NULL;
			//_childCount--;  // taken care of in next line
			_MakeContiguous();
		}
*/

		void Node::_DeleteByItr(AtomMapItr target) {
			// unsafe!  assumes all critical checks have been performed!
			Atom* atm = target->second;
			_children.erase(target);
			delete atm;
		}

/*		
		void Node::_MakeContiguous() {
			_childCount = 0;
			for(int i=0; i < MAXOBJS; i++) {
				if(_children[i] != NULL) {
					_children[_childCount] = _children[i];
					_childCount++;
				}
			}
			for(int i=_childCount; i<MAXOBJS; i++) {
				_children[i] = NULL;
			}
		}
*/

		void Node::_Purge() {
			// this should be more thorough?
			/*
			_MakeContiguous();
			for(int i=0; i<_childCount; i++) {
				_DeleteByIndex(i);
				//delete _children[i];
				//_children[i] = NULL;
			}
			*/
			/*
			for(AtomMapItr i = _children.begin(); i != _children.end(); ) {
				_DeleteByItr(i);
				++i;
			}
			*/
			for(AtomMapItr i = _children.begin(), next_i = i; i!= _children.end(); i = next_i) {
				++next_i;
				_DeleteByItr(i);
				//_children.erase(i);
			}
		}

/*
		void* GetRawData() {
			return NULL;
		}
*/

		void Node::Tick(int time) {
			//Atom::Tick(time);
			/*
			for(int i=0; i<_childCount; i++) {
				_children[i]->Tick(time);
				if(_children[i]->wasUpdated)
					*Log << "We got a live one!  "  << _children[i]->identity << std::endl;
				_children[i]->wasUpdated = false;
				if(_children[i]->wasUpdated)
					*Log << "What the shit?" << std::endl;
			}
			*/
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
