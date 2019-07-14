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
//#include "TestMachine.h"
#include "ShadowInteger.h"
#include "Notype.h"

namespace jmb {
	
	namespace common {
		
		const char Video::type = 0x7E;
		
		Video::Video() {
			Video("");
			// why are the following lines necessary?
			_type = type;
			_windowX = _windowY = 0;
			_windowW = 640;
			_windowH = 480;
			_bufferW = 640;
			_bufferH = 480;
		}
		
		Video::Video(std::string const& name) : Node(name) {
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

		Atom* Video::CtorWrapper(std::string name) {
			return new Video(name);
		}

		int Video::Command(std::string const& cmd) {
			// TODO:  something meaningful
			return Node::Command(cmd);
		}

		std::string Video::GetValueAsStdString() {
			std::stringstream ss;
			ss << "Video " << identity << "@" << std::hex << this;
			return ss.str();
		}

		int Video::_Procedure() {
			//Command("windowWidth -= 1");
			//_windowW--;
			//ShadowInteger* siWinW = (ShadowInteger*)Dereference("windowWidth");
			//std::cout << "windowWidth deref test:  " << siWinW->GetValueAsStdString() << std::endl;
			return Node::_Procedure();
			//return 0;
		}

		Atom* Video::_Interpret(Atom* atm) {
			//std::cout << "Video::_Interpret" << std::endl;
			//return Atom::_Interpret(atm);
			return new Video(atm);
		}

		void* Video::ReadAtom(const Atom* atm) {
			return (void*)this; //shrug
		}

		void Video::Tick(int time) {
			// tick the ShadowIntegers
			for(int i=0; i<_childCount; i++) {
				_children[i]->Tick(time);
			}
			// observe updates
			if(((ShadowInteger*)_winX_SI)->wasUpdated ||
			   ((ShadowInteger*)_winY_SI)->wasUpdated ||
			   ((ShadowInteger*)_winW_SI)->wasUpdated ||
			   ((ShadowInteger*)_winH_SI)->wasUpdated) {
				std::cout << "Debug:  " << _windowX << " " << _windowY << " " << _windowW << " " << _windowH << std::endl;
				// move window
				SDL_SetWindowPosition((SDL_Window*)_Window, _windowX, _windowY);
				// size window
				SDL_SetWindowSize((SDL_Window*)_Window, _windowW, _windowH);
				// unset wasUpdated for those
				((ShadowInteger*)_winX_SI)->wasUpdated = false;
				((ShadowInteger*)_winY_SI)->wasUpdated = false;
				((ShadowInteger*)_winW_SI)->wasUpdated = false;
				((ShadowInteger*)_winH_SI)->wasUpdated = false;
			}
			// (temporarily ignore buffer size updates)
			((ShadowInteger*)_bufW_SI)->wasUpdated = false;
			((ShadowInteger*)_bufH_SI)->wasUpdated = false;
			// observe window position changes
			SDL_GetWindowPosition((SDL_Window*)_Window, &_windowX, &_windowY);
			SDL_GetWindowSize((SDL_Window*)_Window, &_windowW, &_windowH);
			// draw buffer to screen
			SDL_UpdateWindowSurface((SDL_Window*)_Window);
			// blank buffer
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

				_winX_SI = (void*)new ShadowInteger("windowPosX", &_windowX);
				_winY_SI = (void*)new ShadowInteger("windowPosY", &_windowY);
				_winW_SI = (void*)new ShadowInteger("windowWidth", &_windowW);
				_winH_SI = (void*)new ShadowInteger("windowHeight", &_windowH);
				_bufW_SI = (void*)new ShadowInteger("bufferWidth", &_bufferW);
				_bufH_SI = (void*)new ShadowInteger("bufferHeight", &_bufferH);
				AddChild((ShadowInteger*)_winX_SI);
				AddChild((ShadowInteger*)_winY_SI);
				AddChild((ShadowInteger*)_winW_SI);
				AddChild((ShadowInteger*)_winH_SI);
				AddChild((ShadowInteger*)_bufW_SI);
				AddChild((ShadowInteger*)_bufH_SI);
			}
		}

	}
	
}
