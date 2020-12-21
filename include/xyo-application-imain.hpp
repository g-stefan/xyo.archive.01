//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_APPLICATION_IMAIN_HPP
#define XYO_APPLICATION_IMAIN_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#include "xyo-managedmemory-tmemory.hpp"
#endif

namespace XYO {
	namespace Application {
		using namespace XYO::ManagedMemory;

		class IMain : public virtual Object {
				XYO_INTERFACE(IMain);

			public:
				virtual int main(int cmdN, char *cmdS[]) = 0;
		};

	};
};

#define XYO_APPLICATION_MAIN_STD(T) \
	static int XYOApplicationMain_(int cmdN, char *cmdS[])\
	{\
		T application;\
		return (static_cast<XYO::Application::IMain *>(&application))->main(cmdN, cmdS);\
	};\
	int main(int cmdN, char *cmdS[])\
	{\
		int retV;\
		XYO::ManagedMemory::TIfHasInitMemory<T>::initMemory();\
		retV = XYOApplicationMain_(cmdN, cmdS);\
		return retV;\
	}

#define XYO_APPLICATION_MAIN_CSTD(applicationMain) \
	int main(int cmdN, char *cmdS[])\
	{\
		return applicationMain(cmdN, cmdS);\
	}

#ifdef XYO_OS_WINDOWS

#ifndef XYO_SYSTEM_SHELL_HPP
#include "xyo-system-shell.hpp"
#endif

#define XYO_APPLICATION_WINMAIN_STD(T) \
	static int XYOApplicationMain_(int cmdN, char *cmdS[])\
	{\
		T application;\
		return (static_cast<XYO::Application::IMain *>(&application))->main(cmdN, cmdS);\
	};\
	int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)\
	{\
		char exeName[MAX_PATH];\
		int cmdN;\
		char** cmdS;\
		int retV;\
		XYO::ManagedMemory::TIfHasInitMemory<T>::initMemory();\
		GetModuleFileName(nullptr, exeName, MAX_PATH);\
		XYO::Shell::mainArgsSet(exeName, GetCommandLineA(), cmdN, cmdS);\
		retV = XYOApplicationMain_(cmdN, cmdS);\
		XYO::Shell::mainArgsDelete(cmdN, cmdS);\
		return retV;\
	}

#define XYO_APPLICATION_WINMAIN_CSTD(applicationMain) \
	int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)\
	{\
		char exeName[MAX_PATH];\
		int cmdN;\
		char** cmdS;\
		int retV;\
		GetModuleFileName(nullptr, exeName, MAX_PATH);\
		XYO::Shell::mainArgsSet(exeName, GetCommandLineA(), cmdN, cmdS);\
		retV = applicationMain(cmdN, cmdS);\
		XYO::Shell::mainArgsDelete(cmdN, cmdS);\
		return retV;\
	}

#endif

#endif

