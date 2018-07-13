/*
 *  String.h
 *  Test
 *
 *  Created by james on 7/10/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef STRING_H
#define STRING_H

#include "Object.h"

namespace jmb {
	
	namespace common {

		class String : public Object {
		public:
			String();
			String(std::string const& name);
			virtual ~String();
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
			//virtual int OperatorSub(Object* obj); // -=
			//virtual int OperatorMul(Object* obj); // *=
			//virtual int OperatorDiv(Object* obj); // /=
			//virtual int OperatorPow(Object* obj); // ^=
			//std::string identity;
			//Object* owner;
		protected:
			//std::string _GetPath();
			//void _Purge();
			int _Procedure();
			std::string _Interpret(Object* obj);
			//void* _data;
			//char _type;
			//private:
			//unsigned int _GetOwnedObjectIndex(std::string const& name);
			//unsigned int _GetOwnedObjectIndex(Object* obj);
			//Object* _GetOwnedObject(std::string const& name);
			//void _MakeContiguous();
			//void _DeleteByIndex(unsigned int idx);
			
			//Object* _ownedObjects[MAXOBJS];
			//int _ownedObjectCount;
			//bool mapThrough;
		};
		
	}
	
}

#endif //STRING_H