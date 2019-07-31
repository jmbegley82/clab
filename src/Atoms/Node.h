/*
 *  Node.h
 *  Test
 *
 *  Created by james on 7/14/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef NODE_H
#define NODE_H

#include "Atom.h"

#define MAXOBJS 32

namespace jmb {
	
	namespace common {
	
		class Node : public Atom {
		public:
			Node();
			Node(std::string const& name);
			Node(const Atom* atm);
			virtual ~Node();
			static Atom* CtorWrapper(std::string name);
			static const char type;
			virtual Atom* Dereference(std::string const& name);
			//virtual int Command(std::string const& cmd);
			virtual int AddChild(Atom* atm);
			virtual int DelChild(Atom* atm);
			virtual int DelChild(std::string const& name);
			virtual int FreeChild(Atom* atm);
			virtual int OperatorEqu(Atom* atm);
			//virtual void* GetRawData();
			virtual void Tick(int time);
		protected:
			virtual int _Procedure();
			virtual int _Declarate(std::string const& declarator,
						std::string const& subject);
			virtual Atom* _Interpret(Atom* atm);
			unsigned int _GetChildIndex(std::string const& name);
			unsigned int _GetChildIndex(Atom* atm);
			Atom* _GetChild(std::string const& name);
			void _DeleteByIndex(unsigned int idx);
			void _MakeContiguous();
			void _Purge();
			Atom* _children[MAXOBJS];
			int _childCount;
			bool _mapThrough;
		};
	
	}

}

#endif //NODE_H