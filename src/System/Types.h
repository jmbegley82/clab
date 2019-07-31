/*
 * Types.h
 * 07/13/2019
 * JMB
 */

#ifndef JMTYPES_H
#define JMTYPES_H

#include <string>
#include <map>
#include "Atom.h"

namespace jmb {
	namespace common {
		/*
		class Types {
		public:
			Types();
			~Types();
			void AddMapping(std::string const& name, Atom* (*CtorWrapper)(std::string const& id));
			Atom* CreateNew(std::string const& type, std::string const& name);
		private:
			typedef std::map<std::string, Atom* (*)(std::string)> _typeMap;
			typedef _typeMap::iterator _tmItr;
			_typeMap _types;
		};
		*/
		namespace Types {
			void AddMapping(std::string const& name, Atom* (*CtorWrapper)(std::string));
			Atom* CreateNew(std::string const& type, std::string const& name);
			typedef std::map<std::string, Atom* (*)(std::string)> _typeMap;
			typedef _typeMap::iterator _tmItr;
			static _typeMap _types;
		}
	}
}

#endif //JMTYPES_H
