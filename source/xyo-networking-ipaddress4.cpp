//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-networking-ipaddress4.hpp"

namespace XYO {
	namespace Networking {

		IPAddress4::IPAddress4() {
			port = 0;
		};

		void IPAddress4::copy(IPAddress4 &addr) {
			ip.copy(addr.ip);
			port = addr.port;
		};

	};
};


