//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_NETWORKING_IPADDRESS6_HPP
#define XYO_NETWORKING_IPADDRESS6_HPP

#ifndef XYO_NETWORKING_IP6_HPP
#	include "xyo-networking-ip6.hpp"
#endif

namespace XYO {
	namespace Networking {
		using namespace XYO::ManagedMemory;

		class IPAddress6 : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(IPAddress6);

			public:
				IP6 ip;
				uint16_t port;

				XYO_EXPORT IPAddress6();
				XYO_EXPORT void copy(IPAddress6 &addr);
		};

	};
};

#endif
