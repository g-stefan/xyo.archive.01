//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_APPLICATION_VERSION__OS_WINDOWS_RC_HPP
#	define XYO_APPLICATION_VERSION__OS_WINDOWS_RC_HPP
// clang-format off

#define XYO_RC 1

#define XYO_APPLICATION_VERSION_INFO(versionName,appName,description) \
	1 VERSIONINFO\
	FILEVERSION versionName##_VERSION_ABCD\
	PRODUCTVERSION versionName##_VERSION_ABCD\
	{\
		BLOCK "StringFileInfo"\
		{\
			BLOCK "040904E4"\
			{\
				VALUE "CompanyName", versionName##_COMPANY "\000"\
				VALUE "FileDescription", description "\000"\
				VALUE "FileVersion", versionName##_VERSION_STR "\000"\
				VALUE "InternalName", appName "\000"\
				VALUE "LegalCopyright", versionName##_COPYRIGHT "\000"\
				VALUE "ProductName", description "\000"\
				VALUE "ProductVersion", versionName##_VERSION_STR "\000"\
				VALUE "OriginalFilename", appName "\000"\
				VALUE "Copyright", versionName##_COPYRIGHT "\000"\
				VALUE "Contact", versionName##_CONTACT "\000"\
				VALUE "Company", versionName##_COMPANY "\000"\
				VALUE "Publisher", versionName##_PUBLISHER "\000"\
				VALUE "Build", versionName##_VERSION_STR_BUILD  "\000"\
				VALUE "BuildDate",versionName##_VERSION_STR_DATETIME "\000"\
			}\
		}\
		BLOCK "VarFileInfo"\
		{\
			VALUE "Translation", 0x409, 1252\
		}\
	}

// clang-format on
#endif

#ifdef XYO_COMPILE_DYNAMIC_LIBRARY
#	define XYO_APPLICATION_MANIFEST(fileName) 2 24 fileName
#else
#	define XYO_APPLICATION_MANIFEST(fileName) 1 24 fileName
#endif
