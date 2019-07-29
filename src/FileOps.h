/*
 * FileOps.h (pulled from Atma)
 * 07/29/2019
 * jmb
 */

#ifndef FILEOPS_H
#define FILEOPS_H

#include <string>

namespace jmb {
	namespace common {
		std::string GetHomePrefix();
		std::string GetAppPrefix();
		std::string GetLogPrefix();
		int SetHomePrefix(std::string const& path);
		int SetAppPrefix(std::string const& path);
		int SetLogPrefix(std::string const& path);
		std::string InitHomePrefix();
		std::string InitAppPrefix();
		std::string InitLogPrefix();
		void EnsureTrailingSlash(std::string &path);
		bool IsDirectory(std::string const& path);
		bool IsWritableDirectory(std::string const& path);
		int MakeDir(std::string const& name);
		int RemoveFile(std::string const& name);
	}
}

#endif //FILEOPS_H
