//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_STREAM_IWRITE_HPP
#define XYO_STREAM_IWRITE_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#include "xyo-managedmemory-tmemory.hpp"
#endif

namespace XYO {
	namespace Stream {
		using namespace XYO::ManagedMemory;

		class IWrite : public virtual Object {
				XYO_INTERFACE(IWrite);

			public:

				virtual size_t write(const void *input, size_t length) = 0;
		};

	};
};

#endif

