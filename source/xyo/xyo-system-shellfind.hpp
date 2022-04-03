//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_SYSTEM_SHELLFIND_HPP
#define XYO_SYSTEM_SHELLFIND_HPP

#ifndef XYO_ENCODING_STRING_HPP
#	include "xyo-encoding-string.hpp"
#endif

namespace XYO {
	namespace System {
		using namespace XYO::DataStructures;
		using namespace XYO::Encoding;

		typedef struct SShellFind_ ShellFind_;

		class ShellFind : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(ShellFind);

			protected:
				ShellFind_ *shellFind_;
				bool isValid_;

			public:
				XYO_EXPORT ShellFind();
				XYO_EXPORT ~ShellFind();

				char *name;
				bool isFile;
				bool isDirectory;
				bool isReadOnly;

				inline operator bool() const {
					return isValid_;
				};

				XYO_EXPORT bool find(const char *name_);
				XYO_EXPORT bool next();
				XYO_EXPORT void close();
		};
	};
};

#endif
