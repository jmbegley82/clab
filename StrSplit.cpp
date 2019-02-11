#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

#include "StrSplit.h"

namespace jmb
{
	
	namespace common {
		
		CommandSplit::CommandSplit(std::string const& cmd, std::string const& token)
		{
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
			
			if(op == "") {
				target = ""; // for good measure
				subject = cmd;
			}
		}

		std::string DeSpace(std::string const& text) {
			// returns a string similar to text, but without spaces
			std::string retval = "";
			const char* input = text.c_str();
			char c;
			int i =0;
			while(input[i]) {
				c = input[i];
				if(!isspace(c)) {
					retval += c;
				}
				i++;
			}
			return retval;
		}
	}
}
