#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cassert>

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
				ncmd.erase(0, pos+token.length());
				right = ncmd;
			}
			else
			{
				left = "";
				right = "";
			}
		}
		
		Sentence::Sentence(std::string const& cmd) {
			declarator = subject = op = target = "";
			
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
					op = "=";
				}
				
				subject = ncmd.substr(0, pos);
				// op is set
				size_t offset = subject.length() + op.length();
				size_t length = ncmd.length() - offset;
				target = ncmd.substr(offset, length);
			} else {
				// no operator found; set subject to whole cmd
				subject = cmd;
			}
			
			// at this point, subject op and target are set
			// now see if there appears to be a declarator
			//
			if(subject != "") {
				// subjEnd = position of last non-space in subject
				int declBegin = -1;
				int declEnd   = -1;
				int subjBegin = -1;
				int subjEnd   = subject.length() - 1;
				const char* subj = subject.c_str();
				while(subjEnd >= 0 && isspace(subj[subjEnd])) subjEnd--;
				assert(subjEnd >= 0);  // otherwise, subject was empty

				subjBegin = subjEnd;
				while(subjBegin > 0 && !isspace(subj[subjBegin])) subjBegin--;
				declEnd = subjBegin;
				while(declEnd > 0 && isspace(subj[declEnd])) declEnd--;
				declBegin = declEnd;
				while(declBegin > 0 && !isspace(subj[declBegin])) declBegin--;

				if(declEnd != 0) declarator = subject.substr(declBegin, (declEnd + 1) - declBegin);
				subject = subject.substr(subjBegin, (subjEnd + 1) - subjBegin);
			}

			// this will need to change to allow statements like
			// "Float f1" with no operator
			if(declarator == "" && op == "") {
				target = ""; // for good measure
				subject = cmd;
			}
		}

		std::string DeSpace(std::string const& text) {
			// returns a string similar to text, but without spaces
			std::string retval = "";
			const char* input = text.c_str();
			char c;
			int i = 0;
			bool withinQuotes = false;
			while(input[i]) {
				c = input[i];
				if(c == '\"') withinQuotes = !withinQuotes;
				if(withinQuotes || !isspace(c)) {
					retval += c;
				}
				i++;
			}
			return retval;
		}
	}
}
