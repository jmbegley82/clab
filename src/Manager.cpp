/*
 *  Manager.cpp
 *  Test
 *
 *  Created by james on 6/10/19.
 *  Copyright 2019 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_mixer.h>
//#include <SDL_ttf.h>
#include "StringStuff.h"
#include "Manager.h"
#include "Node.h"
#include "Integer.h"
#include "Float.h"
#include "String.h"
#include "ShadowInteger.h"
#include "Video.h"
#include "Notype.h"

namespace jmb {
	
	namespace common {
		
		const char Manager::type = 0x7F;
		
		Manager::Manager() {
			Manager("");
			// why are the following lines necessary?
			_type = type;
		}
		
		Manager::Manager(std::string const& name) : Node(name) {
			_type = type;
			_Init();
		}

		Manager::Manager(const Atom* atm) : Node(atm) {
			assert(0); // this too seems unnecessary
			Manager(atm->identity);
			isEphemeral = true;
			char t = ((Atom*)atm)->GetType();
			if(t == Manager::type) {
				// only valid conversion is Manager to (Atom*)Manager
				Manager* nod = (Manager*)atm;
				for(int i=0; i<MAXOBJS; i++) {
					_children[i] = nod->_children[i];
				}
			}// else assert(t == Manager::type);
		}
		
		Manager::~Manager() {
			//std::cout << "Manager::~Atom" << std::endl;
			if(!isEphemeral) _Purge();
		}

		Atom* Manager::CtorWrapper(std::string name) {
			return new Manager(name);
		}

		int Manager::Command(std::string const& cmd) {
			// TODO:  something meaningful
			return Node::Command(cmd);
		}

		std::string Manager::GetValueAsStdString() {
			std::stringstream ss;
			ss << "Manager " << identity << "@" << std::hex << this;
			return ss.str();
		}

		int Manager::_Procedure() {
			//Command("windowWidth -= 1");
			//_windowW--;
			//ShadowInteger* siWinW = (ShadowInteger*)Dereference("windowWidth");
			//std::cout << "windowWidth deref test:  " << siWinW->GetValueAsStdString() << std::endl;
			return Node::_Procedure();
			//return 0;
		}

		Atom* Manager::_Interpret(Atom* atm) {
			//std::cout << "Manager::_Interpret" << std::endl;
			//return Atom::_Interpret(atm);
			return new Manager(atm);
		}

		void* Manager::ReadAtom(const Atom* atm) {
			return (void*)this; //shrug
		}

		void Manager::Tick(int ms) {
			//Atom::Tick(ms);
			//Command("");
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				// something meaningful
			}
			if(VideoMgr != NULL) {
				((Video*)VideoMgr)->Tick(ms);
			}
		}

		void Manager::_Init() {
			Command("Video VideoMgr");
			VideoMgr = (Video*)Dereference("VideoMgr");
		}

	}
	
}
