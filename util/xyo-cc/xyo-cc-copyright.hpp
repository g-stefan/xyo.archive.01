//
// XYO CC
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_CC_COPYRIGHT_HPP
#define XYO_CC_COPYRIGHT_HPP

#define XYO_CC_COPYRIGHT            "Copyright (c) Grigore Stefan"
#define XYO_CC_PUBLISHER            "Grigore Stefan"
#define XYO_CC_COMPANY              XYO_CC_PUBLISHER
#define XYO_CC_CONTACT              "g_stefan@yahoo.com"
#define XYO_CC_FULL_COPYRIGHT       XYO_CC_COPYRIGHT " <" XYO_CC_CONTACT ">"

#ifndef XYO_RC

namespace XYOCC {
	namespace Copyright {
		const char *copyright();
		const char *publisher();
		const char *company();
		const char *contact();
		const char *fullCopyright();
	};
};

#endif
#endif
