//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_ALGORITHM_RANDOMMT_HPP
#define XYO_ALGORITHM_RANDOMMT_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#include "xyo-managedmemory-tmemory.hpp"
#endif

namespace XYO {
	namespace Algorithm {
		using namespace XYO::ManagedMemory;

		class RandomMT : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(RandomMT);
			protected:
				int index;
				uint32_t mt[624];
				uint32_t value;
			public:

				XYO_EXPORT RandomMT();
				XYO_EXPORT void seed(uint32_t);
				XYO_EXPORT uint32_t nextRandom();
				XYO_EXPORT uint32_t getValue();
				XYO_EXPORT void copy(RandomMT &value);
		};

	};
};

#endif
