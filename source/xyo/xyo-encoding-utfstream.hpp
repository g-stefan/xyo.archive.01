//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_ENCODING_UTFSTREAM_HPP
#define XYO_ENCODING_UTFSTREAM_HPP

#ifndef XYO_ENCODING_UTF_HPP
#	include "xyo-encoding-utf.hpp"
#endif

#ifndef XYO_STREAM_IREAD_HPP
#	include "xyo-stream-iread.hpp"
#endif

#ifndef XYO_STREAM_IWRITE_HPP
#	include "xyo-stream-iwrite.hpp"
#endif

namespace XYO {
	namespace Encoding {
		using namespace XYO::DataStructures;
		using namespace XYO::ManagedMemory;
		using namespace XYO::Stream;

		struct UtfStreamMode {
				enum {
					None = 0,
					Utf8 = 1,
					Utf16 = 2,
					Utf32 = 3
				};
		};

		class Utf8Read : public virtual IRead {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(Utf8Read);

			protected:
				char utf8Input[8];
				TPointerX<IRead> input;
				int mode;
				int index;
				int size;

			public:
				XYO_EXPORT Utf8Read();
				XYO_EXPORT ~Utf8Read();

				XYO_EXPORT bool open(IRead *input_, int mode_);

				inline operator bool() const {
					return input;
				};

				XYO_EXPORT size_t read(void *output, size_t length);

				XYO_EXPORT void close();
		};

		class Utf8Write : public virtual IWrite {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(Utf8Write);

			protected:
				char utf8Output[8];
				TPointerX<IWrite> output;
				int mode;
				int index;
				int size;

			public:
				XYO_EXPORT Utf8Write();
				XYO_EXPORT ~Utf8Write();

				XYO_EXPORT bool open(IWrite *output_, int mode_);

				inline operator bool() const {
					return output;
				};

				XYO_EXPORT size_t write(const void *input, size_t length);

				XYO_EXPORT void close();
		};

	};

};

#endif
