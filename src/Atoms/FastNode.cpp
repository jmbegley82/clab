/*
 *  FastNode.cpp
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
#include "FastNode.h"
#include "Integer.h"
#include "Float.h"
#include "String.h"
#include "Notype.h"

namespace jmb {
	
	namespace common {
		
		const char FastNode::type = 0x12;
		
		FastNode::FastNode() {
			FastNode("");
		}
		
		FastNode::FastNode(std::string const& name) : NodeBase(name) {
			_childCount = 0;
			_children = NULL;
			SetMaxChildren(DEFAULT_MAXCHILDREN);
			for(int i=0; i<_maxChildren; i++) {
				_children[i] = NULL;
			}
			_mapThrough = true;
			_type = type;
		}

		FastNode::FastNode(const Atom* atm) : NodeBase(atm) {
			assert(0);  // not implemented!
			FastNode(atm->identity);
			isEphemeral = true;
			char t = ((Atom*)atm)->GetType();
			if(t == FastNode::type) {
				// only valid conversion is FastNode to (Atom*)FastNode
				FastNode* nod = (FastNode*)atm;
				for(int i=0; i<DEFAULT_MAXCHILDREN; i++) {
					_children[i] = nod->_children[i];
				}
			}// else assert(t == FastNode::type);
		}
		
		FastNode::~FastNode() {
			//*Log << "FastNode::~Atom" << std::endl;
			if(!isEphemeral) _Purge();
			if(_children) free(_children);
		}

		Atom* FastNode::CtorWrapper(std::string name) {
			return new FastNode(name);
		}

		int FastNode::AddChild(Atom* atm) {
			if(_childCount >= _maxChildren)
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
		
		int FastNode::DelChild(Atom* atm) {
			int idx = _GetChildIndex(atm);
			if(idx == _maxChildren) return -1;  // not found
			_DeleteByIndex(idx);
			return 0;
		}
		
		int FastNode::DelChild(std::string const& name) {
			unsigned int idx = _GetChildIndex(name);
			if(idx == _maxChildren) return -1; // not found
			_DeleteByIndex(idx);
			return 0;
		}
		
		int FastNode::FreeChild(Atom* atm) {
			int idx = _GetChildIndex(atm);
			if(idx == _maxChildren) return -1; // not found
			_children[idx] = NULL;
			_MakeContiguous();
			return 0;
		}
		
		int FastNode::OperatorEqu(Atom* atm) {
			*Log << "FastNode::" << __FUNCTION__ << ": stub: " << atm->identity << std::endl;
			return 0; //NI
		}

		int FastNode::GetMaxChildren() {
			return _maxChildren;
		}

		int FastNode::SetMaxChildren(int count) {
			int retval = 0;
			if(_childCount >0) _MakeContiguous();

			// if count is less than current number of children, it's a no-go
			if(count < _childCount) return -1;

			// go ahead and set _maxChildren now
			_maxChildren = count;

			// back up the current contents of _children
			Atom** bup = NULL;
			if(_childCount >0) {
				bup = (Atom**)malloc(_childCount*sizeof(Atom*));
				for(int i=0; i<_childCount; i++) {
					bup[i] = _children[i];
				}
			}

			// if _children is not NULL, erase it
			if(_children) {
				free(_children);
				_children = NULL;
			}
			_children = (Atom**)malloc(_maxChildren*sizeof(Atom*));
			if(bup) {
				for(int i=0; i<_childCount; i++) {
					_children[i] = bup[i];
				}
				free(bup);
			}
			for(int i=_childCount; i<_maxChildren; i++) {
				_children[i] = NULL;
			}
			return retval;
		}

		int FastNode::_Procedure() {
			Atom::_Procedure();
			for(int i=0; i<_childCount; i++) {
				_children[i]->Command("");
			}
			return 0;
		}

		Atom* FastNode::_Interpret(Atom* atm) {
			//*Log << "FastNode::_Interpret" << std::endl;
			return new FastNode(atm);
		}
		
		unsigned int FastNode::_GetChildIndex(std::string const& name) {
			// return _maxChildren if not found
			unsigned int retval;
			for(retval=0; retval<_maxChildren; retval++) {
				if(_children[retval] != NULL &&
				   _children[retval]->identity == name) {
					break;
				}
			}
			return retval;
		}
		
		unsigned int FastNode::_GetChildIndex(Atom* atm) {
			unsigned int retval;
			for(retval=0; retval<_maxChildren; retval++) {
				if(_children[retval] == atm) {
					break;
				}
			}
			return retval;
		}
		
		Atom* FastNode::_GetChild(std::string const& name) {
			// should only get a one-name path
			// no slashes and definitely no operators!
			Atom* retval = NULL;
			int idx = _GetChildIndex(name);
			if(idx < _maxChildren) retval = _children[idx];
			return retval;
		}
		
		void FastNode::_DeleteByIndex(unsigned int idx) {
			// unsafe!  assumes all critical checks have been performed
			delete _children[idx];
			_children[idx] = NULL;
			_MakeContiguous();
		}
		
		void FastNode::_MakeContiguous() {
			_childCount = 0;
			for(int i=0; i < _maxChildren; i++) {
				if(_children[i] != NULL) {
					_children[_childCount] = _children[i];
					_childCount++;
				}
			}
			for(int i=_childCount; i<_maxChildren; i++) {
				_children[i] = NULL;
			}
		}
		
		void FastNode::_Purge() {
			// this should be more thorough?
			_MakeContiguous();
			for(int i=0; i<_childCount; i++) {
				_DeleteByIndex(i);
			}
		}

		void FastNode::Tick(int time) {
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
