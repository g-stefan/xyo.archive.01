//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_SYSTEM_CONSOLE_HPP
#define XYO_SYSTEM_CONSOLE_HPP

#ifndef XYO__DEPENDENCY_HPP
#include "xyo--dependency.hpp"
#endif

namespace XYO {
	namespace System {
		namespace Console {

			XYO_EXPORT bool keyHit();
			XYO_EXPORT char getChar();

		};
	};
};

#endif

