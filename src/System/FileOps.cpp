/*
 * FileOps.cpp (yanked from Atma)
 * 07/29/2019
 * jmb
 */

#include <deque>
#include <cassert>
#include <iostream>
#include <fstream>

#if defined __linux__ || defined __APPLE__ || defined __FREEBSD__ || defined CLAB_PS3
#include <unistd.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#elif defined _MSC_VER
#include <direct.h>
#include "msvs_dirent.h"
#endif //platforms with dirent.h and pwd.h, else platforms without

#if defined __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif //__APPLE__

#if defined __LINUX__
#include <linux/limits.h>
#endif //__LINUX__

#if defined __FREEBSD__
#include <limits.h>
#endif //__FREEBSD

#include "FileOps.h"
#include "StringManip.h"
#include "config.h"
//#include "toaster.h"

using std::string;
using std::ofstream;
using std::deque;

namespace jmb {
	namespace common {

		static string _homePrefix = "";
		static string _appPrefix = "";
		static string _logPrefix = "";

		string GetHomePrefix() {
			return _homePrefix;
		}

		string GetAppPrefix() {
			return _appPrefix;
		}

		string GetLogPrefix() {
			return _logPrefix;
		}

		int SetHomePrefix(string path) {
			int retval = 0;
			// validate path
			_homePrefix = path;
			return retval;
		}

		int SetAppPrefix(string path) {
			int retval = 0;
			// validate path
			_appPrefix = path;
			return retval;
		}

		int SetLogPrefix(string path) {
			int retval = 0;
			// validate path
			_logPrefix = path;
			return retval;
		}

		string InitHomePrefix() {
			string retval = "";
#if defined __APPLE__
#error Apple platform support not added yet!
#elif defined _MSC_VER
#error Windows support not added yet!
#elif (defined __linux__ && !defined __ANDROID__) || defined __FREEBSD__
			passwd* pw = getpwuid(getuid());
			retval = pw->pw_dir;
#elif defined __ANDROID__
#error Android support not added yet!
#elif defined CLAB_PS3
			retval = "/dev_usb000";
#endif // platforms
			_homePrefix = retval;
			return retval;
		}

		string InitAppPrefix() {
			string retval = "";
#if defined __APPLE__
#error Apple platform support not added yet!
#elif defined _MSC_VER
#error Windows support not added yet!
#elif (defined __linux__ && !defined __ANDROID__) || defined __FREEBSD__
			retval = string(PREFIX);
#elif defined __ANDROID__
#error Android support not added yet!
#elif defined CLAB_PS3
			retval = "/dev_usb000";
#endif // platforms
			_appPrefix = retval;
			return retval;
		}

		string InitLogPrefix() {
			string retval = "";
#if defined __APPLE__
#error Apple platform support not added yet!
#elif defined _MSC_VER
#error Windows support not added yet!
#elif (defined __linux__ && !defined __ANDROID__) || defined __FREEBSD__
			retval = "/tmp";
#elif defined __ANDROID__
#error Android support not added yet!
#elif defined CLAB_PS3
			retval = "/dev_usb000";
#endif // platforms
			_logPrefix = retval;
			return retval;
		}

		void EnsureTrailingSlash(string &path) {
			if (path == "")
				path = "/";
			else {
				if (path[path.length() - 1] != '/' && path[path.length()] - 1 != '\\')
					path = path + "/";
			}
		}
		
		bool IsDirectory(string const& path) {
			// should this check for os-specific trailing character?
			DIR* dfd = opendir(path.c_str());
			if (dfd == NULL) return false;
			closedir(dfd);
			return true;
		}

		bool IsWritableDirectory(string const& path) {
			// tested successfully on Windows and Linux so far
			// make sure path is a directory
			if(!IsDirectory(path)) return false;

			// check writability with a test file
			string testFilePath = path;
			EnsureTrailingSlash(testFilePath);
			testFilePath += "testfile.dat";
			int writable = 0;
			// 0  = unknown
			// 1  = yes
			// -1 = no
			ofstream writeTest;
			writeTest.open(testFilePath);
			if (writeTest.is_open()) {
				writable = 1;
				writeTest.close();
#if defined _MSC_VER
				_unlink(testFilePath.c_str());
#else
				unlink(testFilePath.c_str());
#endif //_MSC_VER
			}
			else writable = -1;
			if (writable != 1) return false;
			return true;
		}

		int MakeDir(string const& name) {
			// life will be a lot simpler if only absolute paths are given
			int retval = 0;
			string uname = name;
			ReplaceString(uname, "\\", "/");
			string tmpname = uname;
			deque<string> subdirs;
			while (tmpname != "") {
				CommandSplit CSSlash(tmpname, "/");
				// first go around, .left will be something like "C:"
				// last one depends on if the given path ends with a slash
				if (CSSlash.left == "" && CSSlash.right == "")
					subdirs.push_back(tmpname);
				else subdirs.push_back(CSSlash.left);
				tmpname = CSSlash.right;
			}

			// subdirs should now contain a list of every subdirectory
			if (subdirs.size() < 2) assert(0); // that can't be good
			string reName = "";
			deque<string>::iterator itr = subdirs.begin();
			while (itr != subdirs.end()) {
				reName += (*itr) + "/";
#if defined _MSC_VER
				retval = _mkdir(reName.c_str());
#elif defined __linux__ || defined __APPLE__ || defined __FREEBSD__
				mode_t dirMode = 0775;
				retval = mkdir(reName.c_str(), dirMode);
#endif // os-specific mkdir
				itr++;
			}
			return retval;
		}

		int RemoveFile(string const& name)
		{
			// make sure name is an absolute path
			//   (on windows, the 2nd char of name needs to be ':')
			//   (elsewhere, the 1st char needs to be '/')
			if (name.length() < 3) return -1;

#if defined _MSC_VER
			if (name[1] != ':') {
				assert(0);
				return -2;
			}
#elif defined __linux__ || defined __APPLE__ || defined __FREEBSD__
			if (name[0] != '/') {
				assert(0);
				return -2;
			}
#endif //os-specific absolute dir test


			// make sure name is under HOME_PREFIX
			CommandSplit CSHome(name, GetHomePrefix());
			if (!(CSHome.left == "" && CSHome.right != "")) return -3;

			// if name is a directory,
			//   \ for each entry in directory, RemoveFile(entry)
			//   \ then rmdir the directory itself
			//   \ return 0
			// if name is a file,
			//   \ delete file (unlink)
			//   \ return 0
			// return -1

			DIR* dfd = opendir(name.c_str());
			if (dfd != NULL) {
				// it's a directory
				// delete everything under it
				struct dirent* dirList;
				while ((dirList = readdir(dfd)) != NULL) {
					std::string subName(dirList->d_name);
					if (subName != "." && subName != "..") {
						RemoveFile(name + "/" + subName);
					}
				}
				closedir(dfd);
#if defined _MSC_VER
				_rmdir(name.c_str());
#else
				rmdir(name.c_str());
#endif //_MSC_VER
				return 0;
			}

			// assume it's a regular file otherwise
#if defined _MSC_VER
			_unlink(name.c_str());
#else
			unlink(name.c_str());
#endif //_MSC_VER
			return 0;
		}

	}
}
