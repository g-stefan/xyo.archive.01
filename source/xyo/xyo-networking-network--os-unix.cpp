//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO__DEPENDENCY_HPP
#	include "xyo--dependency.hpp"
#endif

#ifdef XYO_OS_UNIX

#	include "xyo-networking-network.hpp"

namespace XYO {
	namespace Networking {
		namespace Network {

			bool isValid() {
				return true;
			};

		};
	};
};

#endif
