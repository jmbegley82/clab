/*
 * Clab.cpp
 * 07/14/2019
 * jmb
 */

#include <string>
#include "Clab.h"
#include "Log.h"
#include "Atom.h"
#include "Node.h"
#include "Notype.h"
#include "Integer.h"
#include "Float.h"
#include "String.h"
#include "ShadowInteger.h"
#include "Types.h"
#include "config.h"
#include "toaster.h"

using std::string;
using jmb::common::Atom;
using jmb::common::Node;
using jmb::common::Notype;
using jmb::common::Integer;
using jmb::common::Float;
using jmb::common::String;
using jmb::common::ShadowInteger;
using jmb::common::Types::AddMapping;

namespace jmb {
	namespace common {
		int ClabInit() {
			int retval = 0;  // TODO:  something meaningful with this?
			SetLogFile("");
			AddMapping("Atom", Atom::CtorWrapper);
			AddMapping("Notype", Notype::CtorWrapper);
			AddMapping("Node", Node::CtorWrapper);
			AddMapping("Integer", Integer::CtorWrapper);
			AddMapping("String", String::CtorWrapper);
			AddMapping("Float", Float::CtorWrapper);
			AddMapping("ShadowInteger", ShadowInteger::CtorWrapper);
			//AddMapping("Video", Video::CtorWrapper);
			return retval;
		}

		string ClabVersionString() {
			return string(TOASTER(PACKAGE_NAME)) + " " + string(TOASTER(PACKAGE_VERSION)) + " built on " + __DATE__ + " at " + __TIME__;
		}

		int ClabVersionMajor() {
			return CLAB_VERSION_MAJOR;
		}
		
		int ClabVersionMinor() {
			return CLAB_VERSION_MINOR;
		}
	}
}
