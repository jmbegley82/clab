/*
 * NodeBase.cpp
 * 08/20/19
 * jmb
 *
 */

#include <string>
#include "NodeBase.h"
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

