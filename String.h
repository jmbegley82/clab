/*
 *  String.h
 *  Test
 *
 *  Created by james on 2/3/19.
 *  Copyright 2019 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef STRING_H
#define STRING_H

#include <string>
#include "Atom.h"


namespace jmb {

	namespace common {

		class String : public Atom {
		public:
			String();
			String(std::string const& name);
			String(const Atom* atm);
			~String();
			static const char type;
			
			//virtual Atom* Dereference(std::string const& name);
			//virtual int Command(std::string const& cmd);
			//virtual int Command(std::string const& op, Atom* target);
			virtual void SetValue(std::string const& val);
			virtual std::string GetValueAsStdString();
			//virtual std::string GetAbsolutePath();
			virtual void Debug();
			virtual int OperatorEqu(Atom* atm); //  =
			virtual int OperatorAdd(Atom* atm); // +=
			//virtual int OperatorSub(Atom* atm); // -=
			//virtual int OperatorMul(Atom* atm); // *=
			//virtual int OperatorDiv(Atom* atm); // /=
			//virtual int OperatorPow(Atom* atm); // ^=
			virtual void* GetRawData();
		protected:
			virtual int _Procedure();
			virtual Atom* _Interpret(Atom* atm);
			//char _type;
		private:
			std::string ReadAtom(const Atom* atm);
			std::string _data;
		};
		
	}

}

#endif //STRING_H
