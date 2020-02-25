//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_XMLPARSER_HPP
#define XYO_DATASTRUCTURES_XMLPARSER_HPP

#ifndef XYO_DATASTRUCTURES_XML_HPP
#include "xyo-datastructures-xml.hpp"
#endif

#ifndef XYO_PARSER_INPUT_HPP
#include "xyo-parser-input.hpp"
#endif

#ifndef XYO_STREAM_STREAMX_HPP
#include "xyo-stream-streamx.hpp"
#endif

namespace XYO {
	namespace DataStructures {
		using namespace XYO::ManagedMemory;
		using namespace XYO::Stream;
		using namespace XYO::Parser;

		struct XMLParserMode {
			enum {
				Normal = 0,
				Trim = 1,
				Indentation4Spaces = 2,
				IndentationTab = 3
			};
		};

		class XMLReader : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(XMLReader);

			public:

				TPointerX<Input> input;

				XYO_EXPORT XMLReader();
				XYO_EXPORT ~XMLReader();
				XYO_EXPORT void activeDestructor();
				XYO_EXPORT bool open(Input *input_);
				XYO_EXPORT bool open(IRead *iRead_);
				XYO_EXPORT void close();
				XYO_EXPORT bool isSpace();
				XYO_EXPORT bool ignoreSpace();
				XYO_EXPORT bool readName(String &name);
				XYO_EXPORT bool readAttributes(typename XMLDocument::Attributes &attributes);
				XYO_EXPORT bool process(XMLDocument &document, int mode);
				XYO_EXPORT TPointer<XMLDocument> read(int mode = XMLParserMode::Normal);

				XYO_EXPORT static TPointer<XMLDocument> load(const char *fileName, int mode = XMLParserMode::Normal);
		};

		class XMLWriter : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(XMLWriter);

			public:

				TPointerX<IWrite> iWrite;

				XYO_EXPORT XMLWriter();
				XYO_EXPORT ~XMLWriter();
				XYO_EXPORT void activeDestructor();
				XYO_EXPORT bool open(IWrite *input_);
				XYO_EXPORT void close();

				inline bool write(const String &value) {
					return StreamX::write(*iWrite, value);
				};

				XYO_EXPORT bool writeIndentationBegin(int mode, int level);
				XYO_EXPORT bool writeIndentationEnd(int mode);
				XYO_EXPORT bool indentationIsEmpty(String &value, int mode);
				XYO_EXPORT bool writeIndentationTrim(String &value, int mode);
				XYO_EXPORT bool indentationIsContentBranch(XMLDocument &document, int mode);
				XYO_EXPORT bool write(XMLDocument &document, int mode = XMLParserMode::Normal, int level = 0);

				XYO_EXPORT static bool save(XMLDocument &xml, const char *fileName, int mode = XMLParserMode::Normal);
		};

	};
};

#endif
