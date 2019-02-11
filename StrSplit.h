#ifndef STRSPLIT_H
#define STRSPLIT_H

#include <string>


namespace jmb {
	
	namespace common {
		/*
		 class Commandant
		 {
		 public:
		 Commandant(std::string const &cmd);
		 std::string left, op, right;
		 };
		 */
		
		class CommandSplit {
		public:
			CommandSplit(std::string const &cmd, std::string const &token);
			std::string left, right;
		};
		
		class Sentence {
		public:
			Sentence(std::string const& cmd);
			std::string subject, op, target;
			// predicate being op + target
		};

		std::string DeSpace(std::string const& text);
	}
	
}

#endif //STRSPLIT_H
