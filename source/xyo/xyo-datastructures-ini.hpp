//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_INI_HPP
#define XYO_DATASTRUCTURES_INI_HPP

#ifndef XYO_DATASTRUCTURES_TDYNAMICARRAY_HPP
#include "xyo-datastructures-tdynamicarray.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TREDBLACKTREE_HPP
#include "xyo-datastructures-tredblacktree.hpp"
#endif

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

namespace XYO {
	namespace DataStructures {
		using namespace XYO::ManagedMemory;
		using namespace XYO::Encoding;

		struct INILineType {
			enum {
				None = 0,
				Comment = 1,
				Section = 2,
				Value = 3
			};
		};

		struct INILine: Object {
			int type;
			String key;
			String value;

			inline INILine() {
				type = INILineType::None;
			};

			inline INILine(const INILine &line) {
				type = line.type;
				key = line.key;
				value = line.value;
			};

			inline INILine(INILine &&line) {
				type = line.type;
				key = std::move(line.key);
				value = std::move(line.value);
			};

			inline INILine &operator=(const INILine &line) {
				type = line.type;
				key = line.key;
				value = line.value;
				return *this;
			};

			inline INILine &operator=(INILine &&line) {
				type = line.type;
				key = std::move(line.key);
				value = std::move(line.value);
				return *this;
			};

			inline ~INILine() {
			};

			static inline void initMemory() {
				String::initMemory();
			};

			inline void activeDestructor() {
				type = INILineType::None;
				key.activeDestructor();
				value.activeDestructor();
			};
		};

		typedef TDynamicArray<INILine> INIFile;

		namespace INIFileX {
			XYO_EXPORT bool load(const char *fileName, INIFile &iniFile);
			XYO_EXPORT bool save(const char *fileName, INIFile &iniFile);
			XYO_EXPORT bool hasSection(INIFile &iniFile, const char *section);
			XYO_EXPORT size_t count(INIFile &iniFile, const char *section, const char *key);
			XYO_EXPORT bool get(INIFile &iniFile, const char *section, const char *key, String &value, size_t index = 0);
			XYO_EXPORT bool set(INIFile &iniFile, const char *section, const char *key, const char *value, size_t index = 0);
			XYO_EXPORT bool removeKey(INIFile &iniFile, const char *section, const char *key, size_t index = 0);
			XYO_EXPORT bool addSection(INIFile &iniFile, const char *section);
			XYO_EXPORT bool removeSection(INIFile &iniFile, const char *section);
			XYO_EXPORT bool sectionIndex(INIFile &iniFile, const char *section, size_t &index);
			XYO_EXPORT bool sectionLastIndex(INIFile &iniFile, const char *section, size_t &index);
			XYO_EXPORT bool joinSection(INIFile &iniFile, const char *section, INIFile &iniSource, const char *sectionSource);
			XYO_EXPORT bool hasKeyWithValue(INIFile &iniFile, const char *section, const char *key, const char *value);
			XYO_EXPORT bool insert(INIFile &iniFile, const char *section, const char *key, const char *value);
			XYO_EXPORT bool getValues(INIFile &iniFile, const char *section, const char *key, TDynamicArray<String> &values);
			XYO_EXPORT bool renameSection(INIFile &iniFile, const char *sectionOld, const char *sectionNew);
			XYO_EXPORT size_t countSection(INIFile &iniFile);
			XYO_EXPORT bool getSection(INIFile &iniFile, size_t index, String &section);
			XYO_EXPORT bool getKeysAndValues(INIFile &iniFile, const char *section, TRedBlackTree<String, String> &keyAndValues);
		};

	};
};

#endif

