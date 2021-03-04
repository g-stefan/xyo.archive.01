//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-managedmemory-tmemory.hpp"
#include "xyo-datastructures-ini.hpp"
#include "xyo-system-file.hpp"
#include "xyo-stream-streamx.hpp"
#include "xyo-encoding-string.hpp"

namespace XYO {
	namespace DataStructures {
		namespace INIFileX {
			using namespace XYO::ManagedMemory;
			using namespace XYO::Stream;
			using namespace XYO::System;
			using namespace XYO::Encoding;

			bool load(const char *fileName, INIFile &iniFile) {
				File file;
				String line;
				String lineX;
				String trimElements = " \t\r\n";
				iniFile.empty();
				size_t index = 0;
				size_t indexValue;
				if(file.openRead(fileName)) {
					while(StreamX::readLn(file, line, 16384)) {
						INILine &iniLine = iniFile[index];
						lineX = String::trimWithElement(line, trimElements);
						if(lineX.isEmpty()) {
							iniLine.type = INILineType::None;
							++index;
							continue;
						};
						if(lineX[0] == ';') {
							iniLine.type = INILineType::Comment;
							iniLine.value = lineX;
							++index;
							continue;
						};
						if(lineX[0] == '[') {
							iniLine.type = INILineType::Section;
							iniLine.value = lineX;
							++index;
							continue;
						};
						if(String::indexOf(lineX, "=", 0, indexValue)) {
							iniLine.type = INILineType::Value;
							iniLine.key = String::substring(lineX, 0, indexValue);
							iniLine.value = String::substring(lineX, indexValue + 1);
							++index;
							continue;
						};
						iniLine.type = INILineType::None;
						iniLine.value = lineX;
						++index;
					};
					file.close();
					return true;
				};
				return false;
			};

			bool save(const char *fileName, INIFile &iniFile) {
				File file;
				if(file.openWrite(fileName)) {
					size_t k;
					for(k = 0; k < iniFile.length(); ++k) {
						switch(iniFile[k].type) {
							case INILineType::Comment:
								StreamX::write(file, iniFile[k].value);
								StreamX::write(file, "\r\n");
								break;
							case INILineType::Section:
								StreamX::write(file, iniFile[k].value);
								StreamX::write(file, "\r\n");
								break;
							case INILineType::Value:
								StreamX::write(file, iniFile[k].key);
								StreamX::write(file, "=");
								StreamX::write(file, iniFile[k].value);
								StreamX::write(file, "\r\n");
								break;
							default:
								if(iniFile[k].value.length() > 0) {
									StreamX::write(file, iniFile[k].value);
								};
								StreamX::write(file, "\r\n");
								break;
						};
					};
					file.close();
					return true;
				};
				return false;
			};

			bool hasSection(INIFile &iniFile, const char *section) {
				size_t k;
				String sectionX;
				sectionX << "[" << section << "]";
				for(k = 0; k < iniFile.length(); ++k) {
					if(iniFile[k].type == INILineType::Section) {
						if(iniFile[k].value == sectionX) {
							return true;
						};
					};
				};
				return false;
			};

			size_t count(INIFile &iniFile, const char *section, const char *key) {
				size_t count = 0;
				size_t k;
				String sectionX;
				bool inSection = false;
				sectionX << "[" << section << "]";
				for(k = 0; k < iniFile.length(); ++k) {
					if(iniFile[k].type == INILineType::Section) {
						if(inSection) {
							return count;
						};
						if(iniFile[k].value == sectionX) {
							inSection = true;
						};
						continue;
					};
					if((iniFile[k].type == INILineType::Value) && inSection) {
						if(iniFile[k].key == key) {
							++count;
						};
					};
				};
				return count;
			};

			bool get(INIFile &iniFile, const char *section, const char *key, String &value, size_t index) {
				size_t k;
				String sectionX;
				bool inSection = false;
				sectionX << "[" << section << "]";
				for(k = 0; k < iniFile.length(); ++k) {
					if(iniFile[k].type == INILineType::Section) {
						if(inSection) {
							return false;
						};
						if(iniFile[k].value == sectionX) {
							inSection = true;
						};
						continue;
					};
					if((iniFile[k].type == INILineType::Value) && inSection) {
						if(iniFile[k].key == key) {
							if(index == 0) {
								value = iniFile[k].value;
								return true;
							};
							--index;
						};
					};
				};
				return false;
			};

			bool set(INIFile &iniFile, const char *section, const char *key, const char *value, size_t index) {
				size_t k;
				String sectionX;
				bool inSection = false;
				sectionX << "[" << section << "]";
				for(k = 0; k < iniFile.length(); ++k) {
					if(iniFile[k].type == INILineType::Section) {
						if(inSection) {
							int lastK = k - 1;
							for(; k > 0; --k) {
								if(iniFile[k].type == INILineType::Value) {
									lastK = k + 1;
								};
							};
							INILine &iniLine = iniFile.insert(lastK);
							iniLine.type = INILineType::Value;
							iniLine.key = key;
							iniLine.value = value;
							return true;
						};
						if(iniFile[k].value == sectionX) {
							inSection = true;
						};
						continue;
					};
					if(inSection) {
						if(iniFile[k].type == INILineType::Value) {
							if(iniFile[k].key == key) {
								if(index == 0) {
									iniFile[k].value = value;
									return true;
								};
								--index;
							};
						};
					};
				};
				if(inSection == false) {
					iniFile[k].type = INILineType::Section;
					iniFile[k].value = sectionX;
					++k;
				};
				while(index > 0) {
					iniFile[k].type = INILineType::Value;
					iniFile[k].key = key;
					iniFile[k].value = "";
					++k;
					--index;
				};
				iniFile[k].type = INILineType::Value;
				iniFile[k].key = key;
				iniFile[k].value = value;
				return true;
			};

			bool removeKey(INIFile &iniFile, const char *section, const char *key, size_t index) {
				size_t k;
				String sectionX;
				bool inSection = false;
				sectionX << "[" << section << "]";
				for(k = 0; k < iniFile.length(); ++k) {
					if(iniFile[k].type == INILineType::Section) {
						if(inSection) {
							return false;
						};
						if(iniFile[k].value == sectionX) {
							inSection = true;
						};
						continue;
					};
					if((iniFile[k].type == INILineType::Value) && inSection) {
						if(iniFile[k].key == key) {
							if(index > 0) {
								--index;
								continue;
							};
							iniFile.remove(k);
							return true;
						};
					};
				};
				return false;
			};

			bool addSection(INIFile &iniFile, const char *section) {
				size_t k;
				String sectionX;
				sectionX << "[" << section << "]";
				for(k = 0; k < iniFile.length(); ++k) {
					if(iniFile[k].type == INILineType::Section) {
						if(iniFile[k].value == sectionX) {
							return true;
						};
					};
				};
				iniFile[k].type = INILineType::Section;
				iniFile[k].value = sectionX;
				return true;
			};

			bool removeSection(INIFile &iniFile, const char *section) {
				size_t k;
				String sectionX;
				sectionX << "[" << section << "]";
				for(k = 0; k < iniFile.length(); ++k) {
					if(iniFile[k].type == INILineType::Section) {
						if(iniFile[k].value == sectionX) {
							size_t endK = k;
							for(; endK < iniFile.length(); ++endK) {
								if(iniFile[endK].type == INILineType::Section) {
									break;
								};
							};
							size_t index = k;
							for(; k < endK; ++k) {
								iniFile.remove(index);
							};
							return true;
						};
					};
				};
				return true;
			};

			bool sectionIndex(INIFile &iniFile, const char *section, size_t &index) {
				size_t k;
				String sectionX;
				sectionX << "[" << section << "]";
				for(k = 0; k < iniFile.length(); ++k) {
					if(iniFile[k].type == INILineType::Section) {
						if(iniFile[k].value == sectionX) {
							index = k;
							return true;
						};
					};
				};
				return false;
			};

			bool sectionLastIndex(INIFile &iniFile, const char *section, size_t &index) {
				size_t k;
				String sectionX;
				sectionX << "[" << section << "]";
				for(k = 0; k < iniFile.length(); ++k) {
					if(iniFile[k].type == INILineType::Section) {
						if(iniFile[k].value == sectionX) {
							for(++k; k < iniFile.length(); ++k) {
								if(iniFile[k].type == INILineType::Section) {
									--k;
									break;
								};
							};
							index = k;
							return true;
						};
					};
				};
				return false;
			};

			bool joinSection(INIFile &iniFile, const char *section, INIFile &iniSource, const char *sectionSource) {
				size_t indexSource;
				if(sectionIndex(iniSource, sectionSource, indexSource)) {
					if(!hasSection(iniFile, section)) {
						if(!addSection(iniFile, section)) {
							return false;
						};
					};
					size_t indexDestination;
					if(sectionLastIndex(iniFile, section, indexDestination)) {
						if(indexDestination < iniFile.length()) {
							if(iniFile[indexDestination].type == INILineType::None) {
								--indexDestination;
							};
						};
						++indexSource;
						for(; indexSource < iniSource.length(); ++indexSource, ++indexDestination) {
							if(iniSource[indexSource].type == INILineType::Section) {
								break;
							};
							INILine &iniLine = iniFile.insert(indexDestination);
							iniLine.type = iniSource[indexSource].type;
							iniLine.key = iniSource[indexSource].key.value();
							iniLine.value = iniSource[indexSource].value.value();
						};
						return true;
					};
				};
				return false;
			};

			bool hasKeyWithValue(INIFile &iniFile, const char *section, const char *key, const char *value) {
				size_t k;
				String sectionX;
				bool inSection = false;
				sectionX << "[" << section << "]";
				for(k = 0; k < iniFile.length(); ++k) {
					if(iniFile[k].type == INILineType::Section) {
						if(inSection) {
							return false;
						};
						if(iniFile[k].value == sectionX) {
							inSection = true;
						};
						continue;
					};
					if((iniFile[k].type == INILineType::Value) && inSection) {
						if(iniFile[k].key == key) {
							if(iniFile[k].value == value) {
								return true;
							};
						};
					};
				};
				return false;
			};

			bool insert(INIFile &iniFile, const char *section, const char *key, const char *value) {
				size_t k;
				String sectionX;
				bool inSection = false;
				sectionX << "[" << section << "]";
				for(k = 0; k < iniFile.length(); ++k) {
					if(iniFile[k].type == INILineType::Section) {
						if(inSection) {
							int lastK = k - 1;
							for(; k > 0; --k) {
								if(iniFile[k].type == INILineType::Value) {
									lastK = k + 1;
								};
							};
							INILine &iniLine = iniFile.insert(lastK);
							iniLine.type = INILineType::Value;
							iniLine.key = key;
							iniLine.value = value;
							return true;
						};
						if(iniFile[k].value == sectionX) {
							inSection = true;
						};
						continue;
					};
				};
				if(inSection == false) {
					iniFile[k].type = INILineType::Section;
					iniFile[k].value = sectionX;
					++k;
				};
				iniFile[k].type = INILineType::Value;
				iniFile[k].key = key;
				iniFile[k].value = value;
				return true;
			};

			bool getValues(INIFile &iniFile, const char *section, const char *key, TDynamicArray<String> &values) {
				bool found = false;
				size_t k;
				String sectionX;
				bool inSection = false;
				sectionX << "[" << section << "]";
				for(k = 0; k < iniFile.length(); ++k) {
					if(iniFile[k].type == INILineType::Section) {
						if(inSection) {
							return false;
						};
						if(iniFile[k].value == sectionX) {
							inSection = true;
						};
						continue;
					};
					if((iniFile[k].type == INILineType::Value) && inSection) {
						if(iniFile[k].key == key) {
							values.push(iniFile[k].value);
							found = true;
						};
					};
				};
				return found;
			};

			bool renameSection(INIFile &iniFile, const char *sectionOld, const char *sectionNew) {
				size_t index;
				if(sectionIndex(iniFile, sectionOld, index)) {
					String sectionX;
					sectionX << "[" << sectionNew << "]";
					iniFile[index].value = sectionX;
					return true;
				};
				return false;
			};

			size_t countSection(INIFile &iniFile) {
				size_t count = 0;
				size_t k;
				for(k = 0; k < iniFile.length(); ++k) {
					if(iniFile[k].type == INILineType::Section) {
						++count;
					};
				};
				return count;
			};

			bool getSection(INIFile &iniFile, size_t index, String &section) {
				size_t k;
				for(k = 0; k < iniFile.length(); ++k) {
					if(iniFile[k].type == INILineType::Section) {
						if(index == 0) {
							section = String::substring(iniFile[index].value, 1, iniFile[index].value.length() - 2);
							return true;
						};
						--index;
					};
				};
				return false;
			};

		};
	};
};

