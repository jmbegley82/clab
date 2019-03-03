/*
 *  Video.cpp
 *  Test
 *
 *  Created by james on 7/14/18.
 *  Copyright 2018 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "StringStuff.h"
#include "Video.h"
#include "Node.h"
#include "Integer.h"
#include "Float.h"
#include "String.h"
#include "TestMachine.h"
#include "ShadowInteger.h"
#include "Notype.h"

namespace jmb {
	
	namespace common {
		
		const char Video::type = 0x7F;
		
		Video::Video() {
			Video("");
			_type = type;
			_windowX = _windowY = 0;
			_windowW = 640;
			_windowH = 480;
			_bufferW = 640;
			_bufferH = 480;
		}
		
		Video::Video(std::string const& name) : Node(name) {
			/*
			for(int i=0; i<MAXOBJS; i++) {
				_children[i] = NULL;
			}
			_childCount = 0;
			_mapThrough = true;
			_type = type;
			*/
			_type = type;
			_windowX = _windowY = 0;
			_windowW = 640;
			_windowH = 480;
			_bufferW = 640;
			_bufferH = 480;
			_Init();
		}

		Video::Video(const Atom* atm) : Node(atm) {
			assert(0); // this too seems unnecessary
			Video(atm->identity);
			isEphemeral = true;
			char t = ((Atom*)atm)->GetType();
			if(t == Video::type) {
				// only valid conversion is Video to (Atom*)Video
				Video* nod = (Video*)atm;
				for(int i=0; i<MAXOBJS; i++) {
					_children[i] = nod->_children[i];
				}
			}// else assert(t == Video::type);
		}
		
		Video::~Video() {
			//std::cout << "Video::~Atom" << std::endl;
			if(!isEphemeral) _Purge();
		}

		/*
		Atom* Video::Dereference(std::string const& name) {
			Atom* retval = Atom::Dereference(name);  // checks if it's us; rules out name==""
			if(retval->GetType() == Notype::type) {
				delete retval;
				retval = NULL;
			}
			if(_mapThrough) {
				// in case we want to create a Video-derived object with private children
				if(retval == NULL) {
					std::string dname;
					if(name[0] == '/') {
						// absolute path
						dname = name.substr(1);
						retval = GetRoot()->Dereference(dname);
					} else {
						dname = name;
						CommandSplit CSSlash(dname, "/");
						if(CSSlash.left != "") {
							Atom* nextUp = _GetChild(CSSlash.left);
							if(nextUp != NULL) {
								retval = nextUp->Dereference(CSSlash.right);
							}
						} else {
							Atom* nextUp = _GetChild(dname);
							retval = nextUp;
						}
					}
				}
			}
			if(retval == NULL) retval = new Notype(name);
			return retval;
		}
		*/

		int Video::Command(std::string const& cmd) {
			// TODO:  something meaningful
			return Node::Command(cmd);
		}

		std::string Video::GetValueAsStdString() {
			std::stringstream ss;
			ss << "Video " << identity << "@" << std::hex << this;
			return ss.str();
		}

		/*
		int Video::AddChild(Atom* atm) {
			if(_childCount >= MAXOBJS)
				return -1;  // we're full
			if(_GetChild(atm->identity) != NULL)
				return -2; // name exists within this node
			if(atm->parent != NULL) {
				atm->LeaveParent();
			}
			atm->parent = this;
			_children[_childCount] = atm;
			_childCount++;
			return 0;
		}
		
		int Video::DelChild(Atom* atm) {
			int idx = _GetChildIndex(atm);
			if(idx == MAXOBJS) return -1;  // not found
			_DeleteByIndex(idx);
			return 0;
		}
		
		int Video::DelChild(std::string const& name) {
			unsigned int idx = _GetChildIndex(name);
			if(idx == MAXOBJS) return -1; // not found
			_DeleteByIndex(idx);
			return 0;
		}
		
		int Video::FreeChild(Atom* atm) {
			int idx = _GetChildIndex(atm);
			if(idx == MAXOBJS) return -1; // not found
			_children[idx] = NULL;
			_MakeContiguous();
			return 0;
		}
		
		int Video::OperatorEqu(Atom* atm) {
			std::cout << "Video::" << __FUNCTION__ << ": stub: " << atm->identity << std::endl;
			return -1; //NI
		}
		*/

		int Video::_Procedure() {
			/*
			Atom::_Procedure();
			for(int i=0; i<_childCount; i++) {
				_children[i]->Command("");
			}
			*/
			//Command("windowWidth -= 1");
			//_windowW--;
			//ShadowInteger* siWinW = (ShadowInteger*)Dereference("windowWidth");
			//std::cout << "windowWidth deref test:  " << siWinW->GetValueAsStdString() << std::endl;
			return Node::_Procedure();
			//return 0;
		}

		/*
		int Video::_Declarate(std::string const& declarator, std::string const& subject) {
			Atom* noob = NULL;
			if(declarator == "Node") {
				noob = new Node(subject);
			} else if(declarator == "Integer") {
				noob = new Integer(subject);
			} else if(declarator == "Float") {
				noob = new Float(subject);
			} else if(declarator == "String") {
				noob = new String(subject);
			} else if(declarator == "TestMachine") {
				noob = new TestMachine(subject);
			}

			if(noob == NULL) return -3; // invalid declarator
			//else {
				//if(AddChild(noob) != 0) return -2; // already exists or overflow
			return AddChild(noob);
				
			//}
			//return 0;
		}
		*/

		Atom* Video::_Interpret(Atom* atm) {
			//std::cout << "Video::_Interpret" << std::endl;
			//return Atom::_Interpret(atm);
			return new Video(atm);
		}

		/*
		unsigned int Video::_GetChildIndex(std::string const& name) {
			// return MAXOBJS if not found
			unsigned int retval;
			for(retval=0; retval<MAXOBJS; retval++) {
				if(_children[retval] != NULL &&
				   _children[retval]->identity == name) {
					break;
				}
			}
			return retval;
		}
		
		unsigned int Video::_GetChildIndex(Atom* atm) {
			unsigned int retval;
			for(retval=0; retval<MAXOBJS; retval++) {
				if(_children[retval] == atm) {
					break;
				}
			}
			return retval;
		}
		
		Atom* Video::_GetChild(std::string const& name) {
			// should only get a one-name path
			// no slashes and definitely no operators!
			Atom* retval = NULL;
			int idx = _GetChildIndex(name);
			if(idx < MAXOBJS) retval = _children[idx];
			return retval;
		}
		
		void Video::_DeleteByIndex(unsigned int idx) {
			// unsafe!  assumes all critical checks have been performed
			delete _children[idx];
			_children[idx] = NULL;
			//_childCount--;  // taken care of in next line
			_MakeContiguous();
		}
		
		void Video::_MakeContiguous() {
			_childCount = 0;
			for(int i=0; i < MAXOBJS; i++) {
				if(_children[i] != NULL) {
					_children[_childCount] = _children[i];
					_childCount++;
				}
			}
			for(int i=_childCount; i<MAXOBJS; i++) {
				_children[i] = NULL;
			}
		}
		
		void Video::_Purge() {
			// this should be more thorough?
			_MakeContiguous();
			for(int i=0; i<_childCount; i++) {
				_DeleteByIndex(i);
				//delete _children[i];
				//_children[i] = NULL;
			}
		}
		*/

		void* Video::ReadAtom(const Atom* atm) {
			return (void*)this; //shrug
		}

		void Video::_Init() {
			_Window = _Renderer = _Buffer = NULL;
			int ok = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
			if(ok != 0) {
				// error condition...
				std::cout << "ERROR:  Could not initialize SDL:  " << SDL_GetError() <<std::endl;
			} else {
				std::string id = GetValueAsStdString();
				_Window = (void*)SDL_CreateWindow(id.c_str(), _windowX, _windowY, _windowW, _windowH, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
				_Renderer = (void*)SDL_CreateRenderer((SDL_Window*)_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
				assert(_Window != NULL);
				assert(_Renderer != NULL);
				TTF_Init();
				//ShadowInteger* siWinW = new ShadowInteger("windowWidth", &_windowW);
				//AddChild(siWinW);
				AddChild(new ShadowInteger("windowPosX",	&_windowX));
				AddChild(new ShadowInteger("windowPosY",	&_windowY));
				AddChild(new ShadowInteger("windowWidth",	&_windowW));
				AddChild(new ShadowInteger("windowHeight",	&_windowH));
				AddChild(new ShadowInteger("bufferWidth",	&_bufferW));
				AddChild(new ShadowInteger("bufferHeight",	&_bufferH));
			}
		}

	}
	
}
