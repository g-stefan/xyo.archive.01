//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_SYSTEM_FILE_HPP
#define XYO_SYSTEM_FILE_HPP

#ifndef XYO_STREAM_IREAD_HPP
#	include "xyo-stream-iread.hpp"
#endif

#ifndef XYO_STREAM_IWRITE_HPP
#	include "xyo-stream-iwrite.hpp"
#endif

#ifndef XYO_STREAM_ISEEK_HPP
#	include "xyo-stream-iseek.hpp"
#endif

namespace XYO {
	namespace System {
		using namespace XYO::Stream;

		class File_;

		class File : public virtual IRead,
		             public virtual IWrite,
		             public virtual ISeek {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(File);

			protected:
				File_ *value_;
				File *linkOwner_;

			public:
				XYO_EXPORT File();
				XYO_EXPORT ~File();

				XYO_EXPORT bool openRead(const char *);
				XYO_EXPORT bool openWrite(const char *);
				XYO_EXPORT bool openReadAndWrite(const char *);
				XYO_EXPORT bool openAppend(const char *);

				XYO_EXPORT bool openStdIn();
				XYO_EXPORT bool openStdOut();
				XYO_EXPORT bool openStdErr();

				XYO_EXPORT operator bool() const;

				XYO_EXPORT void close();
				XYO_EXPORT void flush();

				XYO_EXPORT size_t read(void *output, size_t length);
				XYO_EXPORT size_t write(const void *input, size_t length);
				XYO_EXPORT bool seekFromBegin(uint64_t x);
				XYO_EXPORT bool seek(uint64_t x);
				XYO_EXPORT bool seekFromEnd(uint64_t x);
				XYO_EXPORT uint64_t seekTell();

				XYO_EXPORT void becomeOwner(File &file_);
				XYO_EXPORT void linkOwner(File &file_);
				XYO_EXPORT void unLinkOwner();
				XYO_EXPORT void transferOwner(File &file_);
		};

	};
};

#endif
