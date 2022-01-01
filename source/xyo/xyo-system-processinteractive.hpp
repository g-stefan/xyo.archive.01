//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_SYSTEM_PROCESSINTERACTIVE_HPP
#define XYO_SYSTEM_PROCESSINTERACTIVE_HPP

#ifndef XYO_STREAM_IREAD_HPP
#include "xyo-stream-iread.hpp"
#endif

#ifndef XYO_STREAM_IWRITE_HPP
#include "xyo-stream-iwrite.hpp"
#endif

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

namespace XYO {
	namespace System {
		using namespace XYO::DataStructures;
		using namespace XYO::Stream;
		using namespace XYO::Encoding;

		class ProcessInteractive_;

		class ProcessInteractive:
			public virtual IRead,
			public virtual IWrite {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(ProcessInteractive);

			protected:

				ProcessInteractive_ *this_;
				ProcessInteractive *linkOwner_;

			public:

				XYO_EXPORT ProcessInteractive();
				XYO_EXPORT ~ProcessInteractive();
				XYO_EXPORT operator bool() const;

				XYO_EXPORT bool execute(const char *cmdLine);
				XYO_EXPORT void join();
				XYO_EXPORT bool isRunning();
				XYO_EXPORT void close();
				XYO_EXPORT bool terminate(const uint32_t waitMilliseconds_);
				XYO_EXPORT uint32_t getReturnValue();

				XYO_EXPORT size_t read(void *output, size_t ln);
				XYO_EXPORT size_t write(const void *input, size_t ln);
				XYO_EXPORT int waitToRead(uint32_t microSeconds);

				XYO_EXPORT void becomeOwner(ProcessInteractive &processInteractive_);
				XYO_EXPORT void linkOwner(ProcessInteractive &processInteractive_);
				XYO_EXPORT void unLinkOwner();
				XYO_EXPORT void transferOwner(ProcessInteractive &processInteractive_);
		};

	};

};

#endif

