//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_STREAM_STREAMX_HPP
#define XYO_STREAM_STREAMX_HPP

#ifndef XYO_STREAM_IREAD_HPP
#include "xyo-stream-iread.hpp"
#endif

#ifndef XYO_STREAM_IWRITE_HPP
#include "xyo-stream-iwrite.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_BUFFER_HPP
#include "xyo-datastructures-buffer.hpp"
#endif

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

namespace XYO {
	namespace Stream {
		namespace StreamX {
			using namespace XYO::DataStructures;
			using namespace XYO::Encoding;

			XYO_EXPORT bool read(IRead &iread, String &out, size_t size);
			XYO_EXPORT bool readLn(IRead &iread, String &out, size_t size);
			XYO_EXPORT size_t write(IWrite &iwrite, const String &data);
			XYO_EXPORT size_t writeLn(IWrite &iwrite, const String &data);
			//
			XYO_EXPORT size_t readToBuffer(IRead &iread, Buffer &buffer, size_t ln);
			XYO_EXPORT size_t writeFromBuffer(IWrite &iwrite, Buffer &buffer);

		};
	};
};

#endif
