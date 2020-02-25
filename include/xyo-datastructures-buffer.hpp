//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_BUFFER_HPP
#define XYO_DATASTRUCTURES_BUFFER_HPP

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

namespace XYO {
	namespace DataStructures {
		using namespace XYO::ManagedMemory;
		using namespace XYO::Encoding;

		class Buffer : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(Buffer);
			public:

				uint8_t *buffer;
				size_t length;
				size_t size;

				XYO_EXPORT Buffer();
				XYO_EXPORT ~Buffer();

				XYO_EXPORT void setSize(size_t);

				XYO_EXPORT void activeDestructor();
				XYO_EXPORT static void initMemory();

				XYO_EXPORT void set(const uint8_t *buf_, size_t size_);

				XYO_EXPORT String toString();
				XYO_EXPORT void fromString(const String &);

				XYO_EXPORT void fromHex(const String &str_);
				XYO_EXPORT String toHex();

				XYO_EXPORT void copy(size_t start, size_t ln, uint8_t *buf_);
				XYO_EXPORT void copy(const Buffer &);
		};

	};

	namespace ManagedMemory {

		template<>
		struct TMemory<DataStructures::Buffer> : TMemoryPoolActive<DataStructures::Buffer> {
		};

	};
};

#endif

