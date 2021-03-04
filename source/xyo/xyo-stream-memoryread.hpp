//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_STREAM_MEMORYREAD_HPP
#define XYO_STREAM_MEMORYREAD_HPP

#ifndef XYO_STREAM_IREAD_HPP
#include "xyo-stream-iread.hpp"
#endif

#ifndef XYO_STREAM_ISEEK_HPP
#include "xyo-stream-iseek.hpp"
#endif

namespace XYO {
	namespace Stream {

		class MemoryRead :
			public virtual IRead,
			public virtual ISeek {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(MemoryRead);

			protected:

				const void *data_;
				size_t size_;
				size_t pos_;

			public:

				XYO_EXPORT MemoryRead();
				XYO_EXPORT ~MemoryRead();
				XYO_EXPORT bool open(const void *data, size_t size);
				XYO_EXPORT operator bool() const;
				XYO_EXPORT void close();
				XYO_EXPORT size_t read(void *output, size_t ln);
				XYO_EXPORT bool seekFromBegin(uint64_t x);
				XYO_EXPORT bool seek(uint64_t x);
				XYO_EXPORT bool seekFromEnd(uint64_t x);
				XYO_EXPORT uint64_t seekTell();

		};

	};
};

#endif
