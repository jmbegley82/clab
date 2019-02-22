/*
 *  TestMachine.h
 *  Test
 *
 *  Created by james on 2/16/19.
 *  Copyright 2019 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TESTMACHINE_H
#define TESTMACHINE_H

#include <string>
#include "Atom.h"


namespace jmb {

	namespace common {

		class TestMachine : public Atom {
		public:
			TestMachine();
			TestMachine(std::string const& name);
			TestMachine(const Atom* atm);
			~TestMachine();
			static const char type;
			
			//virtual Atom* Dereference(std::string const& name);
			virtual int Command(std::string const& cmd);
			//virtual int Command(std::string const& op, Atom* target);
			virtual void SetValue(std::string const& val);
			virtual std::string GetValueAsStdString();
			//virtual std::string GetAbsolutePath();
			virtual void Debug();
			//virtual int OperatorEqu(Atom* atm); //  =
			//virtual int OperatorAdd(Atom* atm); // +=
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
			//int ReadRawTestMachine(Atom* atm);
			//int ReadRawFloat(Atom* atm);
			void* ReadAtom(const Atom* atm);
			void _Init();
			void* _Renderer;
			void* _Window;
			void* _Buffer;
		};
		
	}

}

#endif //TESTMACHINE_H
