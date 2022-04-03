//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO__DEPENDENCY_HPP
#	include "xyo--dependency.hpp"
#endif

#ifdef XYO_OS_WINDOWS

#	include <conio.h>

#	include "xyo-system-console.hpp"

namespace XYO {
	namespace System {
		namespace Console {

			bool keyHit() {
				return static_cast<bool>(_kbhit());
			};

			char getChar() {
				return static_cast<char>(_getch());
			};

		};
	};
};

#endif
