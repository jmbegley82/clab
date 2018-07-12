#include <string>
#include <vector>
#include <algorithm>

#include "StrSplit.h"

namespace jmb
{
	
	namespace common {
		
		//#define STRSPLIT_C
		CommandSplit::CommandSplit(std::string const& cmd, std::string const& token)
		{
#ifndef STRSPLIT_C
			std::string ncmd = cmd;
			size_t pos = ncmd.find(token,0);
			if(pos != std::string::npos)
			{
				left = ncmd.substr(0,pos);
				//dbg left <<"\n";
				//ncmd.erase(0,pos+1);
				ncmd.erase(0, pos+token.length());
				right = ncmd;
				//dbg right <<"\n";
			}
			else
			{
				left = "";
				right = "";
			}
#else
			assert(0); // dont even think about it!
			const char* ncmd = cmd.c_str();
			char lefty[2048] = "";
			char righty[2048] = "";
			//char* lefty = StrSplit((char*)ncmd, (char*)token.c_str(), righty);
			StrSplit((char*)ncmd, (char*)token.c_str(), lefty, righty);
			if(lefty != NULL) left = lefty;
			if(righty != NULL) right = righty;
#endif //STRSPLIT_C
		}
		
		Sentence::Sentence(std::string const& cmd) {
			subject = op = target = "";
			
			std::string ncmd = cmd;
			size_t pos = ncmd.find("=");
			if(pos != std::string::npos) {
				if(pos > 0) {
					pos--;
					op = ncmd.substr(pos,1);
					if(op == "+") {
						op = "+=";
					} else if(op == "-") {
						op = "-=";
					} else if(op == "*") {
						op = "*=";
					} else if(op == "/") {
						op = "/=";
					} else if(op == "^") {
						op = "^=";
					} else {
						op = "=";
						pos++;
					}
				} else {
					// pos = 0
					op = "=";
				}
				
				subject = ncmd.substr(0, pos);
				// op is set
				size_t offset = subject.length() + op.length();
				size_t length = ncmd.length() - offset;
				target = ncmd.substr(offset, length);
			}
			
		}
	}
}