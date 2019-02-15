/*
 *  Float.h
 *  Test
 *
 *  Created by james on 2/2/19.
 *  Copyright 2019 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FLOAT_H
#define FLOAT_H

#include <string>
#include "Atom.h"


namespace jmb {

	namespace common {

		class Float : public Atom {
		public:
			Float();
			Float(std::string const& name);
			Float(const Atom* atm);
			~Float();
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
			double ReadAtom(const Atom* atm);
			double _data;
		};
		
	}

}

#endif //FLOAT_H
