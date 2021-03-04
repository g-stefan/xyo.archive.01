//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_ENCODING_STRING_HPP
#define XYO_ENCODING_STRING_HPP

#ifndef XYO_DATASTRUCTURES_TSTRING_HPP
#include "xyo-datastructures-tstring.hpp"
#endif

namespace XYO {
	namespace Encoding {
		using namespace XYO::DataStructures;

		typedef TStringCore<char> StringCore;
		typedef TStringReference<char> StringReference;
		typedef TString<char> String;
	};
};

#endif

