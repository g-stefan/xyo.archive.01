//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_NETWORING_IP6_HPP
#define XYO_NETWORING_IP6_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#include "xyo-managedmemory-tmemory.hpp"
#endif

namespace XYO {
	namespace Networking {
		using namespace XYO::ManagedMemory;

		class IP6 : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(IP6);
			public:

				uint8_t ip[16];

				XYO_EXPORT IP6();
				XYO_EXPORT void copy(IP6 &ip_);
				XYO_EXPORT bool isInTheSameNetwork(IP6 &ip_, IP6 &mask_);
		};

	};
};

#endif

