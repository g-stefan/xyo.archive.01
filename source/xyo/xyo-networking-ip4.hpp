//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_NETWORING_IP4_HPP
#define XYO_NETWORING_IP4_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#	include "xyo-managedmemory-tmemory.hpp"
#endif

namespace XYO {
	namespace Networking {
		using namespace XYO::ManagedMemory;

		class IP4 : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(IP4);

			public:
				uint8_t ip[4];

				XYO_EXPORT IP4();
				XYO_EXPORT uint32_t toU32();
				XYO_EXPORT void fromU32(uint32_t ip_);
				XYO_EXPORT void copy(IP4 &ip_);
				XYO_EXPORT bool isInTheSameNetwork(IP4 &ip_, IP4 &mask_);
		};

	};
};

#endif
