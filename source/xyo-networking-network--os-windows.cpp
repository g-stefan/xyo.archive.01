//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO__DEPENDENCY_HPP
#include "xyo--dependency.hpp"
#endif

#ifdef XYO_OS_WINDOWS

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>

#include "xyo-networking-network.hpp"
#include "xyo-managedmemory-tsingletonprocess.hpp"

namespace XYO {
	namespace Networking {
		namespace Network {
			using namespace XYO::ManagedMemory;

			class Network_ {
				public:
					bool isValid;

					Network_();
					~Network_();
			};

			Network_::Network_() {
				isValid = false;
				WSADATA wsaData;
				WORD    wVersionRequested = MAKEWORD(2, 2);
				if (WSAStartup(wVersionRequested, &wsaData) == 0) {
					isValid = true;
				};
			};

			Network_::~Network_() {
				if(isValid) {
					WSACleanup();
				};
			};

			bool isValid() {
				return (TSingletonProcess<Network_>::getValue())->isValid;
			};

		};
	};
};

#endif

