/*
 *  Float.h
 *  Test
 *
 *  Created by james on 7/12/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef FLOAT_H
#define FLOAT_H

#include <string>
#include "Object.h"

//#define MAXOBJS 32

namespace jmb {
	
	namespace common {
		
		class Float : public Object {
		public:
			Float();
			Float(std::string const& name);
			~Float();
			static const char type;
			//Float* Dereference(std::string const& name);
			//void AddOwnedFloat(Float* obj);
			//void DelOwnedFloat(std::string const& name);
			//void GiveAway(Float* obj);
			//void LeaveOwner();
			int Command(std::string const& cmd);
			void Tick(unsigned int ms);
			void Debug();
			//void* GetValue();
			//void SetValue(void* val);
			//char GetType();
			int OperatorEqu(Object* obj); //  =
			int OperatorAdd(Object* obj); // +=
			int OperatorSub(Object* obj); // -=
			int OperatorMul(Object* obj); // *=
			int OperatorDiv(Object* obj); // /=
			int OperatorPow(Object* obj); // ^=
			//std::string identity;
			//Float* owner;
		protected:
			//std::string _GetPath();
			//void _Purge();
			int _Procedure();
			double _Interpret(Object* obj);
			//void* _data;
			//char _type;
			//private:
			//unsigned int _GetOwnedObjectIndex(std::string const& name);
			//unsigned int _GetOwnedObjectIndex(Object* obj);
			//Float* _GetOwnedObject(std::string const& name);
			//void _MakeContiguous();
			//void _DeleteByIndex(unsigned int idx);
			
			//Float* _ownedObjects[MAXOBJS];
			//int _ownedObjectCount;
			//bool mapThrough;
		};
	}
	
}

#endif //FLOAT_H