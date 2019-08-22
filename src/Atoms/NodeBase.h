/*
 * NodeBase.h
 * 08/20/19
 * jmb
 *
 */

#ifndef NODEBASE_H
#define NODEBASE_H

#include <string>
#include "Atom.h"

namespace jmb {
	namespace common {

		class NodeBase : public Atom {
		public:
			NodeBase();
			NodeBase(std::string const& name);
			NodeBase(const Atom* atm);
//			virtual ~NodeBase();
//			static Atom* CtorWrapper(std::string name);
//			static const char type;
//			virtual Atom* Dereference(std::string const& name);
			//virtual int Command(std::string const& cmd);
			virtual int AddChild(Atom* atm);
			virtual int DelChild(Atom* atm);
			virtual int DelChild(std::string const& name);
			virtual int FreeChild(Atom* atm);
//			virtual int OperatorEqu(Atom* atm);
			//virtual void* GetRawData();
//			virtual void Tick(int time);
		protected:
//			virtual int _Procedure();
			virtual int _Declarate(std::string const& declarator,
						std::string const& subject);
//			virtual Atom* _Interpret(Atom* atm);
			//unsigned int _GetChildIndex(std::string const& name);
			//unsigned int _GetChildIndex(Atom* atm);
//			Atom* _GetChild(std::string const& name);
//			AtomMapItr _GetChildItr(std::string const& name);
//			AtomMapItr _GetChildItr(Atom* atm);
			//void _DeleteByIndex(unsigned int idx);
//			void _DeleteByItr(AtomMapItr target);
			//void _MakeContiguous();
//			void _Purge();
			//Atom* _children[MAXOBJS];
//			AtomMap _children;
			//int _childCount;
//			bool _mapThrough;
		};
	
	}

}

#endif //NODEBASE_H
