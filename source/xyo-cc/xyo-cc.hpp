//
// XYO CC
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_CC_HPP
#define XYO_CC_HPP

#include "xyo.hpp"

namespace XYOCC {

	using namespace XYO;

	class Application : public virtual IMain {
			XYO_DISALLOW_COPY_ASSIGN_MOVE(Application);

		public:
			inline Application(){};

			void showUsage();
			void showLicense();
			void showVersion();

			int main(int cmdN, char *cmdS[]);
	};

};

#endif
