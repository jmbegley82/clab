/*
 *  Object.h
 *  Test
 *
 *  Created by james on 7/7/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#define MAXOBJS 32

namespace jmb {
	
	namespace common {
		
		class Object {
		public:
			Object();
			Object(std::string const& name);
			virtual ~Object();
			static const char type;
			Object* Dereference(std::string const& name);
			void AddOwnedObject(Object* obj);
			void DelOwnedObject(std::string const& name);
			void GiveAway(Object* obj);
			void LeaveOwner();
			virtual int Command(std::string const& cmd);
			virtual void Tick(unsigned int ms);
			virtual void Debug();
			void* GetValue();
			void SetValue(void* val);
			char GetType();
			virtual int OperatorEqu(Object* obj); //  =
			virtual int OperatorAdd(Object* obj); // +=
			virtual int OperatorSub(Object* obj); // -=
			virtual int OperatorMul(Object* obj); // *=
			virtual int OperatorDiv(Object* obj); // /=
			virtual int OperatorPow(Object* obj); // ^=
			std::string identity;
			Object* owner;
		protected:
			std::string _GetPath();
			void _Purge();
			virtual int _Procedure();
			void* _data;
			char _type;
		//private:
			unsigned int _GetOwnedObjectIndex(std::string const& name);
			unsigned int _GetOwnedObjectIndex(Object* obj);
			Object* _GetOwnedObject(std::string const& name);
			void _MakeContiguous();
			void _DeleteByIndex(unsigned int idx);
			
			Object* _ownedObjects[MAXOBJS];
			int _ownedObjectCount;
			bool mapThrough;
		};
	}
	
}

#endif //OBJECT_H