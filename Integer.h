/*
 *  Integer.h
 *  Test
 *
 *  Created by james on 7/8/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INTEGER_H
#define INTEGER_H

#include "Object.h"

namespace jmb {
	
	namespace common {
		
		class Integer : public Object {
		public:
			Integer();
			Integer(std::string const& name);
			~Integer();
			static const char type;
			//Object* Dereference(std::string const& name);
			//void AddOwnedObject(Object* obj);
			//void DelOwnedObject(std::string const& name);
			//void GiveAway(Object* obj);
			//void LeaveOwner();
			int Command(std::string const& cmd);
			void Tick(unsigned int ms);
			std::string GetValueAsStdString();
			void Debug();
			//void* GetValue();
			//void SetValue(void* val);
			void SetValue(std::string const& val);
			//char GetType();
			int OperatorEqu(Object* obj); //  =
			int OperatorAdd(Object* obj); // +=
			int OperatorSub(Object* obj); // -=
			int OperatorMul(Object* obj); // *=
			int OperatorDiv(Object* obj); // /=
			int OperatorPow(Object* obj); // ^=
			//std::string identity;
			//Object* owner;
		protected:
			//std::string _GetPath();
			// void _Purge();
			int _Procedure();
			int _Interpret(Object* obj);
		//private:
			//unsigned int _GetOwnedObjectIndex(std::string const& name);
			//unsigned int _GetOwnedObjectIndex(Object* obj);
			//Object* _GetOwnedObject(std::string const& name);
			//void _MakeContiguous();
			//void _DeleteByIndex(unsigned int idx);
			
			//Object* _ownedObjects[MAXOBJS];
			//int _ownedObjectCount;
			
			//void* _data;
			//char _type;
			//bool mapThrough;
		};
	}
}

#endif //INTEGER_H
