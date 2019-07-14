/*
 *  Integer.h
 *  Test
 *
 *  Created by james on 8/11/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INTEGER_H
#define INTEGER_H

#include <string>
#include "Atom.h"


namespace jmb {

	namespace common {

		class Integer : public Atom {
		public:
			Integer();
			Integer(std::string const& name);
			Integer(const Atom* atm);
			~Integer();
			static Atom* CtorWrapper(std::string name);
			static const char type;
			
			//virtual Atom* Dereference(std::string const& name);
			virtual int Command(std::string const& cmd);
			//virtual int Command(std::string const& op, Atom* target);
			virtual void SetValue(std::string const& val);
			virtual std::string GetValueAsStdString();
			//virtual std::string GetAbsolutePath();
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
			//char _type;
		private:
			//int ReadRawInteger(Atom* atm);
			//int ReadRawFloat(Atom* atm);
			int ReadAtom(const Atom* atm);
			int _data;
		};
		
	}

}

#endif //INTEGER_H
