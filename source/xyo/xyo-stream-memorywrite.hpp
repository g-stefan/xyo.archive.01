//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_STREAM_MEMORYWRITE_HPP
#define XYO_STREAM_MEMORYWRITE_HPP

#ifndef XYO_STREAM_IWRITE_HPP
#	include "xyo-stream-iwrite.hpp"
#endif

#ifndef XYO_STREAM_ISEEK_HPP
#	include "xyo-stream-iseek.hpp"
#endif

namespace XYO {
	namespace Stream {

		class MemoryWrite : public virtual IWrite,
		                    public virtual ISeek {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(MemoryWrite);

			protected:
				void *data_;
				size_t size_;
				size_t pos_;

			public:
				XYO_EXPORT MemoryWrite();
				XYO_EXPORT ~MemoryWrite();
				XYO_EXPORT bool open(void *data, size_t size);
				XYO_EXPORT operator bool() const;
				XYO_EXPORT void close();
				XYO_EXPORT size_t write(const void *input, size_t length);
				XYO_EXPORT bool seekFromBegin(uint64_t x);
				XYO_EXPORT bool seek(uint64_t x);
				XYO_EXPORT bool seekFromEnd(uint64_t x);
				XYO_EXPORT uint64_t seekTell();
		};

	};
};

#endif
