/*
 *  Video.h
 *  Test
 *
 *  Created by james on 2/24/19.
 *  Copyright 2019 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef VIDEO_H
#define VIDEO_H

#include "Atom.h"
#include "Node.h"

//#define MAXOBJS 32

namespace jmb {
	
	namespace common {
	
		class Video : public Node {
		public:
			Video();
			Video(std::string const& name);
			Video(const Atom* atm);
			virtual ~Video();
			static const char type;
			//virtual Atom* Dereference(std::string const& name);
                        virtual int Command(std::string const& cmd);
                        virtual std::string GetValueAsStdString();
			//virtual int AddChild(Atom* atm);
			//virtual int DelChild(Atom* atm);
			//virtual int DelChild(std::string const& name);
			//virtual int FreeChild(Atom* atm);
			//virtual int OperatorEqu(Atom* atm);
			//virtual void* GetRawData();
		protected:
			virtual int _Procedure();
			//virtual int _Declarate(std::string const& declarator,
			//			std::string const& subject);
			virtual Atom* _Interpret(Atom* atm);
			//unsigned int _GetChildIndex(std::string const& name);
			//unsigned int _GetChildIndex(Atom* atm);
			//Atom* _GetChild(std::string const& name);
			//void _DeleteByIndex(unsigned int idx);
			//void _MakeContiguous();
			//void _Purge();
			//Atom* _children[MAXOBJS];
			//int _childCount;
			//bool _mapThrough;
		private:
                        void* ReadAtom(const Atom* atm);
                        void _Init();
                        void* _Renderer;
                        void* _Window;
                        void* _Buffer;
		};
	
	}

}

#endif //VIDEO_H
