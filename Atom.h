/*
 *  Atom.h
 *  Test
 *
 *  Created by james on 7/13/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

// hold on to your butts.

#ifndef ATOM_H
#define ATOM_H

#include <string>

//#define MAXOBJS 32

namespace jmb {
	
	namespace common {
		
		class Atom {
		public:
			Atom();
			Atom(std::string const& name);
			virtual ~Atom();
			static const char type;
			
			std::string GetPath();
			char GetType();
			std::string identity;
			Atom* parent;
			
			virtual Atom* Dereference(std::string const& name);
			virtual int Command(std::string const& cmd);
			virtual void SetValue(std::string const& val);
			virtual std::string GetValueAsStdString();
			virtual void Debug();
			virtual int OperatorEqu(Atom* atm); //  =
			virtual int OperatorAdd(Atom* atm); // +=
			virtual int OperatorSub(Atom* atm); // -=
			virtual int OperatorMul(Atom* atm); // *=
			virtual int OperatorDiv(Atom* atm); // /=
			virtual int OperatorPow(Atom* atm); // ^=
		protected:
			virtual int _Procedure();
			char _type;
		};
	}
	
}

#endif //ATOM_H