/*
 *  OldNode.cpp
 *  Test
 *
 *  Created by james on 8/19/19.
 *
 */

#include <iostream>
#include <cassert>
#include "Log.h"
#include "Types.h"
#include "StringManip.h"
#include "OldNode.h"
#include "Integer.h"
#include "Float.h"
#include "String.h"
#include "Notype.h"

namespace jmb {
	
	namespace common {
		
		const char OldNode::type = 0x04;
		
		OldNode::OldNode() {
			OldNode("");
		}
		
		OldNode::OldNode(std::string const& name) : Atom(name) {
			for(int i=0; i<MAXOBJS; i++) {
				_children[i] = NULL;
			}
			_childCount = 0;
			_mapThrough = true;
			_type = type;
		}

		OldNode::OldNode(const Atom* atm) : Atom(atm) {
			OldNode(atm->identity);
			isEphemeral = true;
			char t = ((Atom*)atm)->GetType();
			if(t == OldNode::type) {
				// only valid conversion is OldNode to (Atom*)OldNode
				OldNode* nod = (OldNode*)atm;
				for(int i=0; i<MAXOBJS; i++) {
					_children[i] = nod->_children[i];
				}
			}// else assert(t == OldNode::type);
		}
		
		OldNode::~OldNode() {
			//*Log << "OldNode::~Atom" << std::endl;
			if(!isEphemeral) _Purge();
		}

		Atom* OldNode::CtorWrapper(std::string name) {
			return new OldNode(name);
		}
		
		Atom* OldNode::Dereference(std::string const& name) {
			Atom* retval = Atom::Dereference(name);  // checks if it's us; rules out name==""
			if(retval->GetType() == Notype::type) {
				delete retval;
				retval = NULL;
			}
			if(_mapThrough) {
				// in case we want to create a OldNode-derived object with private children
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
		
		int OldNode::AddChild(Atom* atm) {
			if(_childCount >= MAXOBJS)
				return -1;  // we're full
			if(_GetChild(atm->identity) != NULL)
				return -2; // name exists within this node
			if(atm->parent != NULL) {
				atm->LeaveParent();
			}
			atm->parent = this;
			_children[_childCount] = atm;
			_childCount++;
			return 0;
		}
		
		int OldNode::DelChild(Atom* atm) {
			int idx = _GetChildIndex(atm);
			if(idx == MAXOBJS) return -1;  // not found
			_DeleteByIndex(idx);
			return 0;
		}
		
		int OldNode::DelChild(std::string const& name) {
			unsigned int idx = _GetChildIndex(name);
			if(idx == MAXOBJS) return -1; // not found
			_DeleteByIndex(idx);
			return 0;
		}
		
		int OldNode::FreeChild(Atom* atm) {
			int idx = _GetChildIndex(atm);
			if(idx == MAXOBJS) return -1; // not found
			_children[idx] = NULL;
			_MakeContiguous();
			return 0;
		}
		
		int OldNode::OperatorEqu(Atom* atm) {
			*Log << "OldNode::" << __FUNCTION__ << ": stub: " << atm->identity << std::endl;
			return 0; //NI
		}
		
		int OldNode::_Procedure() {
			Atom::_Procedure();
			for(int i=0; i<_childCount; i++) {
				_children[i]->Command("");
			}
			return 0;
		}

		int OldNode::_Declarate(std::string const& declarator, std::string const& subject) {
			Atom* noob = NULL;
			/*
			if(declarator == "OldNode") {
				noob = new OldNode(subject);
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
		
		Atom* OldNode::_Interpret(Atom* atm) {
			//*Log << "OldNode::_Interpret" << std::endl;
			//return Atom::_Interpret(atm);
			return new OldNode(atm);
		}
		
		unsigned int OldNode::_GetChildIndex(std::string const& name) {
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
		
		unsigned int OldNode::_GetChildIndex(Atom* atm) {
			unsigned int retval;
			for(retval=0; retval<MAXOBJS; retval++) {
				if(_children[retval] == atm) {
					break;
				}
			}
			return retval;
		}
		
		Atom* OldNode::_GetChild(std::string const& name) {
			// should only get a one-name path
			// no slashes and definitely no operators!
			Atom* retval = NULL;
			int idx = _GetChildIndex(name);
			if(idx < MAXOBJS) retval = _children[idx];
			return retval;
		}
		
		void OldNode::_DeleteByIndex(unsigned int idx) {
			// unsafe!  assumes all critical checks have been performed
			delete _children[idx];
			_children[idx] = NULL;
			//_childCount--;  // taken care of in next line
			_MakeContiguous();
		}
		
		void OldNode::_MakeContiguous() {
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
		
		void OldNode::_Purge() {
			// this should be more thorough?
			_MakeContiguous();
			for(int i=0; i<_childCount; i++) {
				_DeleteByIndex(i);
				//delete _children[i];
				//_children[i] = NULL;
			}
		}
		/*
		void* GetRawData() {
			return NULL;
		}
		*/

		void OldNode::Tick(int time) {
			//Atom::Tick(time);
			for(int i=0; i<_childCount; i++) {
				_children[i]->Tick(time);
				if(_children[i]->wasUpdated)
					*Log << "We got a live one!  "  << _children[i]->identity << std::endl;
				_children[i]->wasUpdated = false;
				if(_children[i]->wasUpdated)
					*Log << "What the shit?" << std::endl;
			}
		}
	}
	
}
