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

		class Node;
		
		class Atom {
		public:
			Atom();
			Atom(std::string const& name);
			Atom(const Atom* atm);
			virtual ~Atom();
			static const char type;
			bool isEphemeral;
			
			Atom* GetRoot();
			char GetType();
			void LeaveParent();
			std::string identity;
			Node* parent;
			
			virtual Atom* Dereference(std::string const& name);
			virtual int Command(std::string const& cmd);
			virtual int Command(std::string const& op, Atom* target);
			virtual void SetValue(std::string const& val);
			virtual std::string GetValueAsStdString();
			virtual std::string GetAbsolutePath();
			virtual void Debug();
			virtual int OperatorEqu(Atom* atm); //  =
			virtual int OperatorAdd(Atom* atm); // +=
			virtual int OperatorSub(Atom* atm); // -=
			virtual int OperatorMul(Atom* atm); // *=
			virtual int OperatorDiv(Atom* atm); // /=
			virtual int OperatorPow(Atom* atm); // ^=
			virtual void* GetRawData();
		protected:
			virtual int _Procedure();
			virtual Atom* _Interpret(Atom* atm);
			char _type;
		};
	}
	
}

#endif //ATOM_H
