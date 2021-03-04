// Public domain
// http://unlicense.org/
// Created by Grigore Stefan <g_stefan@yahoo.com>

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

void stringReplace(string &data, string toSearch, string replaceWith) {

	size_t pos = data.find(toSearch);
	while(pos != string::npos) {
		data.replace(pos, toSearch.size(), replaceWith);
		pos =data.find(toSearch, pos + replaceWith.size());
	};

};

bool fileReplaceLine(string fileIn_, string fileOut_, map<string, string> &toReplace) {

	fstream fileIn;
	fstream fileOut;
	map<string, string>::iterator index;

	fileIn.open(fileIn_, ios::in);
	fileOut.open(fileOut_, ios::out);

	if (fileIn.is_open()) {
		if (fileOut.is_open()) {

			string line;
			while(getline(fileIn, line)) {
				for ( index = toReplace.begin(); index != toReplace.end(); index++ ) {
					stringReplace(line, index->first, index->second);
				};
				fileOut << line << '\n';
			};

			fileOut.close();
			fileIn.close();
			return true;
		};
		fileIn.close();
	};

	return false;
};

bool fileCompare(string fileName1, string fileName2) {
	std::ifstream file1(fileName1, ifstream::binary|ifstream::ate);
	std::ifstream file2(fileName2, ifstream::binary|ifstream::ate);

	if (file1.fail() || file1.fail()) {
		return false;
	};

	if (file1.tellg() != file2.tellg()) {
		return false;
	};

	file1.seekg(0, ifstream::beg);
	file2.seekg(0, ifstream::beg);

	return equal(istreambuf_iterator<char>(file1.rdbuf()),
			istreambuf_iterator<char>(),
			istreambuf_iterator<char>(file2.rdbuf()));
};

// --

string configFileIn="source/xyo/xyo--config.template.hpp";
string configFileOut="source/xyo/xyo--config.hpp";
string configFileCheck="temp/xyo--config.hpp";

map<string, string> configMap;

void configEnable(string what) {
	string toFind;
	string toReplace;

	toFind="//#define ";
	toFind+=what;

	toReplace="#define ";
	toReplace+=what;

	configMap.insert(pair<string, string>(toFind, toReplace));
};

void configSetPlatform(string value) {
	string toFind;
	string toReplace;

	toFind="//#define XYO_PLATFORM \"unknown\"";

	toReplace="#define XYO_PLATFORM \"";
	toReplace+=value;
	toReplace+="\"";

	configMap.insert(pair<string, string>(toFind, toReplace));
};

// --

int main(int cmdN, char *cmdS[]) {

// -- Operating System
#ifdef XYO_OS_WINDOWS
	configEnable("XYO_OS_WINDOWS");
#endif
#ifdef XYO_OS_UNIX
	configEnable("XYO_OS_UNIX");
#endif
#ifdef XYO_OS_MINGW
	configEnable("XYO_OS_MINGW");
#endif

// -- Compiler
#ifdef XYO_COMPILER_MSVC
	configEnable("XYO_COMPILER_MSVC");
#endif
#ifdef XYO_COMPILER_GCC
	configEnable("XYO_COMPILER_GCC");
#endif

// -- Platform
#define XYO_PLATFORM_STR_B(X) #X
#define XYO_PLATFORM_STR_A(X) XYO_PLATFORM_STR_B(X)
#define XYO_PLATFORM_STR XYO_PLATFORM_STR_A(XYO_PLATFORM)

	configSetPlatform(XYO_PLATFORM_STR);

// -- Application
#ifdef XYO_APPLICATION_64BIT
	configEnable("XYO_APPLICATION_64BIT");
#endif
#ifdef XYO_APPLICATION_32BIT
	configEnable("XYO_APPLICATION_32BIT");
#endif

// -- Thread support
#ifdef XYO_SINGLE_THREAD
	configEnable("XYO_SINGLE_THREAD");
#endif
#ifdef XYO_MULTI_THREAD
	configEnable("XYO_MULTI_THREAD");
#endif

// -- Compile
#ifdef XYO_COMPILE_RELEASE
	configEnable("XYO_COMPILE_RELEASE");
#endif
#ifdef XYO_COMPILE_DEBUG
	configEnable("XYO_COMPILE_DEBUG");
#endif
#ifdef XYO_COMPILE_CRT_STATIC
	configEnable("XYO_COMPILE_CRT_STATIC");
#endif
#ifdef XYO_COMPILE_CRT_DYNAMIC
	configEnable("XYO_COMPILE_CRT_DYNAMIC");
#endif
#ifdef XYO_COMPILE_STATIC_LIBRARY
	configEnable("XYO_COMPILE_STATIC_LIBRARY");
#endif
#ifdef XYO_COMPILE_DYNAMIC_LIBRARY
	configEnable("XYO_COMPILE_DYNAMIC_LIBRARY");
#endif

// -- Debug
#ifdef XYO_MEMORY_LEAK_DETECTOR_VLD
	configEnable("XYO_MEMORY_LEAK_DETECTOR_VLD");
#endif
#ifdef XYO_TMEMORYPOOL_SYSTEM
	configEnable("XYO_TMEMORYPOOL_SYSTEM");
#endif
#ifdef XYO_TMEMORYPOOL_ACTIVE_AS_UNIFIED
	configEnable("XYO_TMEMORYPOOL_ACTIVE_AS_UNIFIED");
#endif
#ifdef XYO_TMEMORYPOOL_ACTIVE_LEVEL_IS_SYSTEM
	configEnable("XYO_TMEMORYPOOL_ACTIVE_LEVEL_IS_SYSTEM");
#endif
#ifdef XYO_TMEMORYPOOL_UNIFIED_AS_SYSTEM
	configEnable("XYO_TMEMORYPOOL_UNIFIED_AS_SYSTEM");
#endif
#ifdef XYO_TMEMORYPOOL_CHECK
	configEnable("XYO_TMEMORYPOOL_CHECK");
#endif
#ifdef XYO_TMEMORYPOOL_CHECK_INFO
	configEnable("XYO_TMEMORYPOOL_CHECK_INFO");
#endif
#ifdef XYO_TMEMORYPOOL_CHECK_COUNT_INFO
	configEnable("XYO_TMEMORYPOOL_CHECK_COUNT_INFO");
#endif
#ifdef XYO_TMEMORYPOOL_CONSTRUCTOR_INFO
	configEnable("XYO_TMEMORYPOOL_CONSTRUCTOR_INFO");
#endif
#ifdef XYO_TMEMORYPOOL_DESTRUCTOR_INFO
	configEnable("XYO_TMEMORYPOOL_DESTRUCTOR_INFO");
#endif
#ifdef XYO_OBJECT_REFERENCE_COUNT_INFO
	configEnable("XYO_OBJECT_REFERENCE_COUNT_INFO");
#endif

	if(!fileReplaceLine(configFileIn, configFileCheck, configMap)) {
		cout << "xyo - configuration check error\n";
		return 1;
	};

	if(!fileCompare(configFileCheck, configFileOut)) {
		if(!fileReplaceLine(configFileIn, configFileOut, configMap)) {
			cout << "xyo - configuration error\n";
			return 1;
		};
	};

	cout << "xyo - configured\n";

	return 0;
};

