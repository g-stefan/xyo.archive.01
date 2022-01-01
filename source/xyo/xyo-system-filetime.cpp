//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO__DEPENDENCY_HPP
#include "xyo--dependency.hpp"
#endif

#include "xyo-system-filetime.hpp"

namespace XYO {
	namespace System {

		using namespace XYO::ManagedMemory;
		using namespace XYO::DataStructures;

		bool FileTime::isChanged(TDynamicArray<FileTime> &x) {
			int k;
			if(!fileTime) {
				return true;
			};

			for(k = 0; k < x.length(); ++k) {
				if(compare(x[k]) < 0) {
					return true;
				};
			};
			return false;
		};

	};
};

