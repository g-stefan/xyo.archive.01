//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_ERROR_HPP
#define XYO_DATASTRUCTURES_ERROR_HPP

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

namespace XYO {
	namespace DataStructures {
		using namespace XYO::Encoding;

		class Error {
			protected:
				String message;
			public:

				inline Error() {
				};

				inline Error(const String &message_) {
					message = message_;
				};

				inline Error(const Error &e) {
					message = e.message;
				};

				inline Error(Error &&e) {
					message = std::move(e.message);
				};

				inline Error &operator=(const Error &e) {
					message = e.message;
					return *this;
				};

				inline Error &operator=(Error &&e) {
					message = std::move(e.message);
					return *this;
				};

				inline String getMessage() {
					return message;
				};

				static inline void initMemory() {
					TMemory<String>::initMemory();
				};
		};

	};
};

#endif
