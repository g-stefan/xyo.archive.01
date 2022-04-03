//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_STREAM_ISEEK_HPP
#define XYO_STREAM_ISEEK_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#	include "xyo-managedmemory-tmemory.hpp"
#endif

namespace XYO {

	namespace Stream {
		using namespace XYO::ManagedMemory;

		class ISeek : public virtual Object {
				XYO_INTERFACE(ISeek);

			public:
				virtual bool seekFromBegin(uint64_t x) = 0;
				virtual bool seek(uint64_t x) = 0;
				virtual bool seekFromEnd(uint64_t x) = 0;
				virtual uint64_t seekTell() = 0;
		};

	};

};

#endif
