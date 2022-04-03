//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_STREAM_IREAD_HPP
#define XYO_STREAM_IREAD_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#	include "xyo-managedmemory-tmemory.hpp"
#endif

namespace XYO {
	namespace Stream {
		using namespace XYO::ManagedMemory;

		class IRead : public virtual Object {
				XYO_INTERFACE(IRead);

			public:
				virtual size_t read(void *output, size_t length) = 0;
		};

	};
};

#endif
