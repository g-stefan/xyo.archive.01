//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-networking-ipaddress6.hpp"

namespace XYO {
	namespace Networking {

		IPAddress6::IPAddress6() {
			port = 0;
		};

		void IPAddress6::copy(IPAddress6 &addr) {
			ip.copy(addr.ip);
			port = addr.port;
		};

	};
};
