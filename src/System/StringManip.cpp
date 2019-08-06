#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <sstream>

#include "StringManip.h"

using std::string;
using std::stringstream;

namespace jmb
{
	
	namespace common {
		
		CommandSplit::CommandSplit(string const& cmd, string const& token)
		{
			string ncmd = cmd;
			size_t pos = ncmd.find(token,0);
			if(pos != string::npos)
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
		
		Sentence::Sentence(string const& cmd) {
			declarator = subject = op = target = "";
			
			string ncmd = cmd;
			size_t pos = ncmd.find("=");
			if(pos != string::npos) {
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
					} else if(op == ":") {
						op = ":=";
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

		void ReplaceString(string& input, string const& from, string const& to) {
			//ReplaceString(input, from, to, NULL, "", "");

			if (from.empty()) return;
			size_t start_pos = 0;
			while ((start_pos = input.find(from, start_pos)) != string::npos) {
				input.replace(start_pos, from.length(), to);
				start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
			}
		}

		string RemovePadding(string const& text) {
			// returns a string with spaces stripped from the beginning and end
			string retval = "";
			/*
			const char* input = text.c_str();
			int i = 0;
			int j = text.length();

			while(i < text.length() && isspace(input[i])) i++;
			while(j > i && isspace(input[j])) j--;

			retval = text.substr(i, j-i);
			*/
			if(text != "") {
				string::const_iterator i = text.begin();
				while(i != text.end() && isspace(*i)) i++;
				string::const_iterator j = text.end();
				while(j > i && isspace(*j)) j--;
				retval = string(i, j);
			}
			return retval;
		}

		bool ValidateStrtod(string const& text) {
			bool retval = true;
			string::const_iterator i = text.begin();
			while(retval && i != text.end()) {
				if(!std::isdigit(*i) && *i != '+' && *i != '-'
					&& *i != '.') retval = false;
				i++;
			}
			return retval;
		}

		string GetHexString(void* obj) {
			stringstream ss;
			ss << std::hex << obj;
			return ss.str();
		}
	}
}
