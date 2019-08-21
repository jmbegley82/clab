/*
 * NodeBase.cpp
 * 08/20/19
 * jmb
 *
 */

#include <string>
#include "NodeBase.h"

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

	}
}

