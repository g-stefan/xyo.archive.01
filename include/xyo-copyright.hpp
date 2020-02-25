//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_COPYRIGHT_HPP
#define XYO_COPYRIGHT_HPP

#define XYO_COPYRIGHT            "Copyright (c) Grigore Stefan"
#define XYO_PUBLISHER            "Grigore Stefan"
#define XYO_COMPANY              XYO_PUBLISHER
#define XYO_CONTACT              "g_stefan@yahoo.com"
#define XYO_FULL_COPYRIGHT       XYO_COPYRIGHT " <" XYO_CONTACT ">"

#ifndef XYO_RC

#ifndef XYO__EXPORT_HPP
#include "xyo--export.hpp"
#endif

namespace XYO {
	namespace Copyright {
		XYO_EXPORT const char *copyright();
		XYO_EXPORT const char *publisher();
		XYO_EXPORT const char *company();
		XYO_EXPORT const char *contact();
		XYO_EXPORT const char *fullCopyright();
	};
};

#endif
#endif
