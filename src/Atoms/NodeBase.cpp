/*
 * NodeBase.cpp
 * 08/20/19
 * jmb
 *
 */

#include <string>
#include "NodeBase.h"
#include "Notype.h"
#include "StringManip.h"
#include "Types.h"

using std::string;

namespace jmb {
	namespace common {

		NodeBase::NodeBase() {
			NodeBase("");
		}

		NodeBase::NodeBase(string const& name) : Atom(name) {
		}

		NodeBase::NodeBase(const Atom* atm) : Atom(atm) {
		}

		Atom* NodeBase::Dereference(string const& name) {
			Atom* retval = Atom::Dereference(name);  // checks if it's us; rules out name==""
			if(retval->GetType() == Notype::type) {
				delete retval;
				retval = NULL;
			}
			if(_mapThrough) {
				// in case we want to create a FastNode-derived object with private children
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
	
		int NodeBase::AddChild(Atom* atm) {
			return -1;
		}

		int NodeBase::DelChild(Atom* atm) {
			return -1;
		}

		int NodeBase::DelChild(string const& name) {
			return -1;
		}
		
		int NodeBase::FreeChild(Atom* atm) {
			return -1;
		}

		Atom* NodeBase::_GetChild(string const& name) {
			return NULL;
		}
	
		int NodeBase::_Declarate(string const& declarator, string const& subject) {
			Atom* noob = NULL;
			// if subject contains any slashes, get a pointer to the NodeBase'd Atom
			// and pass declarator and everything after the rightmost slash to
			//   its _Declarate function

			CommandSplitRev CSPath(subject, "/");
			if(CSPath.left != "" && CSPath.right != "") {
				// the named subject will belong to Node under this one
				Atom* realOwner = Dereference(CSPath.left);
				if(!realOwner) return -1;  // path inaccessible
				if(realOwner->GetType() < 0x10 || realOwner->GetType() > 0x1F)
					return -4;  // it's not any kind of Node, so don't static_cast!
				NodeBase* realNode = static_cast<NodeBase*>(realOwner);
				return realNode->_Declarate(declarator, CSPath.right);
			}
			// else...
			noob = Types::CreateNew(declarator, subject);
			if(noob == NULL) {
				return -3; // invalid declarator
			}
			return AddChild(noob);
		}

	}
}

