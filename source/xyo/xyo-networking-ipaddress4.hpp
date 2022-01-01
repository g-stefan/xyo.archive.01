//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_NETWORKING_IPADDRESS4_HPP
#define XYO_NETWORKING_IPADDRESS4_HPP

#ifndef XYO_NETWORKING_IP4_HPP
#include "xyo-networking-ip4.hpp"
#endif

namespace XYO {
	namespace Networking {
		using namespace XYO::ManagedMemory;

		class IPAddress4 : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(IPAddress4);

			public:

				IP4 ip;
				uint16_t port;

				XYO_EXPORT IPAddress4();
				XYO_EXPORT void copy(IPAddress4 &addr);
		};

	};
};


#endif

