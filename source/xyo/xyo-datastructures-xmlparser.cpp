//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-datastructures-xmlparser.hpp"
#include "xyo-system-file.hpp"

namespace XYO {
	namespace DataStructures {
		using namespace XYO::ManagedMemory;
		using namespace XYO::Stream;
		using namespace XYO::Parser;
		using namespace XYO::System;

		// Reader

		XMLReader::XMLReader() {
			input.pointerLink(this);
		};

		XMLReader::~XMLReader(){};

		void XMLReader::activeDestructor() {
			input.deleteMemory();
		};

		bool XMLReader::open(Input *input_) {
			input = input_;
			return true;
		};

		bool XMLReader::open(IRead *iRead_) {
			input.newMemory();
			if (input->open(iRead_, 16)) {
				return true;
			};
			return false;
		};

		void XMLReader::close() {
			activeDestructor();
		};

		bool XMLReader::isSpace() {
			bool isOk = false;
			while (!input->isEof()) {

				if (input->is1('\x20')) {
					isOk = true;
					continue;
				};

				if (input->is1('\x09')) {
					isOk = true;
					continue;
				};

				if (input->is1('\x0D')) {
					isOk = true;
					continue;
				};

				if (input->is1('\x0A')) {
					isOk = true;
					continue;
				};

				return isOk;
			};
			return false;
		};

		bool XMLReader::ignoreSpace() {
			while (!input->isEof()) {

				if (input->is1('\x20')) {
					continue;
				};

				if (input->is1('\x09')) {
					continue;
				};

				if (input->is1('\x0D')) {
					continue;
				};

				if (input->is1('\x0A')) {
					continue;
				};

				return true;
			};
			return false;
		};

		bool XMLReader::readName(String &name) {
			while (!input->isEof()) {
				if (input->is1('\x20')) {
					return true;
				};
				if (input->is1('\x09')) {
					return true;
				};
				if (input->is1('\x0D')) {
					return true;
				};
				if (input->is1('\x0A')) {
					return true;
				};
				if (input->is('=')) {
					return true;
				};
				if (input->is('/')) {
					return true;
				};
				if (input->is('>')) {
					return true;
				};

				name += input->inputChar;
				input->read();
			};
			return false;
		};

		bool XMLReader::readAttributes(typename XMLDocument::Attributes &attributes) {
			int index = 0;
			bool isOk;
			while (!input->isEof()) {
				if (!ignoreSpace()) {
					return false;
				};

				if (input->is('/')) {
					return true;
				};
				if (input->is('>')) {
					return true;
				};

				attributes[index].newMemory();
				if (!readName(attributes[index]->name)) {
					return false;
				};

				if (!ignoreSpace()) {
					return false;
				};

				if (!input->is1('=')) {
					return false;
				};

				if (!ignoreSpace()) {
					return false;
				};

				if (input->is1('"')) {
					isOk = false;
					while (!input->isEof()) {
						if (input->is1('"')) {
							isOk = true;
							break;
						};
						attributes[index]->value += input->inputChar;
						input->read();
					};
					if (!isOk) {
						return false;
					};

					++index;
					continue;
				};

				if (input->is1('\'')) {
					isOk = false;
					while (!input->isEof()) {
						if (input->is1('\'')) {
							isOk = true;
							break;
						};
						attributes[index]->value += input->inputChar;
						input->read();
					};

					if (!isOk) {
						return false;
					};

					++index;
					continue;
				};

				break;
			};
			return false;
		};

		bool XMLReader::process(XMLDocument &document, int mode) {
			TPointer<typename XMLDocument::Node> node;
			bool isOk;
			while (!input->isEof()) {

				// BOM
				if (input->isN("\xEF\xBB\xBF")) {
					node.newMemory();
					node->type = XMLNodeType::Bom;
					node->name = "\xEF\xBB\xBF";
					document.add(node);
					continue;
				};

				// Declaration / Processing instructions
				if (input->isN("<?")) {
					node.newMemory();
					node->type = XMLNodeType::Declaration;
					isOk = false;
					while (!input->isEof()) {
						if (input->isN("?>")) {
							document.add(node);
							isOk = true;
							break;
						};
						node->name += input->inputChar;
						input->read();
					};
					if (!isOk) {
						return false;
					};
					continue;
				};

				// Document Type Definition
				if (input->isN("<!DOCTYPE")) {
					if (isSpace()) {
						node.newMemory();
						node->type = XMLNodeType::DocumentTypeDefinition;
						isOk = false;
						while (!input->isEof()) {
							if (input->is1('>')) {
								document.add(node);
								isOk = true;
								break;
							};
							node->name += input->inputChar;
							input->read();
						};
						if (!isOk) {
							return false;
						};
						continue;
					};
					return false;
				};

				// Comment
				if (input->isN("<!--")) {
					node.newMemory();
					node->type = XMLNodeType::Comment;
					isOk = false;
					while (!input->isEof()) {
						if (input->isN("-->")) {
							document.add(node);
							isOk = true;
							break;
						};
						node->name += input->inputChar;
						input->read();
					};
					if (!isOk) {
						return false;
					};
					continue;
				};

				// CDATA
				if (input->isN("<![CDATA[")) {
					node.newMemory();
					node->type = XMLNodeType::CDATA;
					isOk = false;
					while (!input->isEof()) {
						if (input->isN("]]>")) {
							document.add(node);
							isOk = true;
							break;
						};
						node->name += input->inputChar;
						input->read();
					};
					if (!isOk) {
						return false;
					};
					continue;
				};

				// Element
				if (input->is1('<')) {
					// end tag ...
					if (input->is('/')) {
						input->push();
						input->set('<');
						return true;
					};

					if (isSpace()) {
						return false;
					};

					node.newMemory();
					node->type = XMLNodeType::Element;

					if (readName(node->name)) {
						node->attributes.newMemory();
						if (readAttributes(*(node->attributes))) {
							if (input->isN("/>")) {
								document.add(node);
								continue;
							};

							if (input->is1('>')) {
								XMLDocument branch(document.add(node));
								if (process(branch, mode)) {
									if (input->isN("</")) {
										if (input->isN(node->name)) {
											if (!ignoreSpace()) {
												return false;
											};
											if (input->is1('>')) {
												continue;
											};
										};
									};
								};
							};
						};
					};

					return false;
				};

				// Content
				node.newMemory();
				node->type = XMLNodeType::Content;
				isOk = false;
				while (!input->isEof()) {
					if (input->is('<')) {
						isOk = true;
						break;
					};
					node->name += input->inputChar;
					input->read();
				};

				if (mode == XMLParserMode::Trim) {
					String tmp = String::trimAscii(node->name);
					if (!tmp.isEmpty()) {
						node->name = tmp;
						document.add(node);
					};

					if (isOk) {
						continue;
					};

					break;
				};

				document.add(node);

				if (isOk) {
					continue;
				};

				// End of document
				break;
			};

			return true;
		};

		TPointer<XMLDocument> XMLReader::read(int mode) {
			TPointer<XMLDocument> retV;

			if (input->read()) {
				retV.newMemory();
				if (process(*retV, mode)) {
					return retV;
				};
			};

			return nullptr;
		};

		TPointer<XMLDocument> XMLReader::load(const char *fileName, int mode) {
			XMLReader xmlReader;
			File file;
			if (file.openRead(fileName)) {
				if (xmlReader.open(&file)) {
					return xmlReader.read(mode);
				};
			};
			return nullptr;
		};

		// Writer

		XMLWriter::XMLWriter() {
			iWrite.pointerLink(this);
		};

		XMLWriter::~XMLWriter(){};

		void XMLWriter::activeDestructor() {
			iWrite.deleteMemory();
		};

		bool XMLWriter::open(IWrite *input_) {
			iWrite = input_;
			return true;
		};

		void XMLWriter::close() {
			activeDestructor();
		};

		bool XMLWriter::writeIndentationBegin(int mode, int level) {
			if (mode == XMLParserMode::Indentation4Spaces) {
				for (; level > 0; --level) {
					if (!write("\x20\x20\x20\x20")) {
						return false;
					};
				};
				return true;
			};
			if (mode == XMLParserMode::IndentationTab) {
				for (; level > 0; --level) {
					if (!write("\x09")) {
						return false;
					};
				};
				return true;
			};
			return true;
		};

		bool XMLWriter::writeIndentationEnd(int mode) {
			if ((mode == XMLParserMode::Indentation4Spaces) || (mode == XMLParserMode::IndentationTab)) {
				if (!write("\x0D\x0A")) {
					return false;
				};
				return true;
			};
			return true;
		};

		bool XMLWriter::indentationIsEmpty(String &value, int mode) {
			if ((mode == XMLParserMode::Indentation4Spaces) || (mode == XMLParserMode::IndentationTab)) {
				return ((String::trimAscii(value)).isEmpty());
			};
			return false;
		};

		bool XMLWriter::writeIndentationTrim(String &value, int mode) {
			if ((mode == XMLParserMode::Indentation4Spaces) || (mode == XMLParserMode::IndentationTab) || (mode == XMLParserMode::Trim)) {
				String tmp = String::trimAscii(value);
				if (!tmp.isEmpty()) {
					if (!write(tmp)) {
						return false;
					};
				};
				return true;
			};
			if (!write(value)) {
				return false;
			};
			return true;
		};

		bool XMLWriter::indentationIsContentBranch(XMLDocument &document, int mode) {
			if ((mode == XMLParserMode::Indentation4Spaces) || (mode == XMLParserMode::IndentationTab)) {
				typename XMLDocument::Branch::Node *node;
				if (!document.root) {
					return true;
				};
				for (node = document.root->head; node != nullptr; node = node->next) {
					if (!node->value) {
						continue;
					};
					if ((node->value->type != XMLNodeType::Content) && (node->value->type != XMLNodeType::Bom)) {
						return false;
					};
				};
				return true;
			};
			return false;
		};

		bool XMLWriter::write(XMLDocument &document, int mode, int level) {
			typename XMLDocument::Branch::Node *node;
			if (!document.root) {
				return true;
			};
			for (node = document.root->head; node != nullptr; node = node->next) {
				if (!node->value) {
					continue;
				};

				if (node->value->type == XMLNodeType::Content) {
					if (indentationIsEmpty(node->value->name, mode)) {
						continue;
					};
				};

				if (!writeIndentationBegin(mode, level)) {
					return false;
				};

				switch (node->value->type) {
				case XMLNodeType::Bom:
					if (!write(node->value->name)) {
						return false;
					};
					break;
				case XMLNodeType::Declaration:
					if (!write("<?")) {
						return false;
					};
					if (!write(node->value->name)) {
						return false;
					};
					if (!write("?>")) {
						return false;
					};
					break;
				case XMLNodeType::DocumentTypeDefinition:
					if (!write("<!DOCTYPE")) {
						return false;
					};
					if (!write(node->value->name)) {
						return false;
					};
					if (!write(">")) {
						return false;
					};
					break;
				case XMLNodeType::Comment:
					if (!write("<!--")) {
						return false;
					};
					if (!write(node->value->name)) {
						return false;
					};
					if (!write("-->")) {
						return false;
					};
					break;
				case XMLNodeType::CDATA:
					if (!write("<![CDATA[")) {
						return false;
					};
					if (!write(node->value->name)) {
						return false;
					};
					if (!write("]]>")) {
						return false;
					};
					break;
				case XMLNodeType::Content:
					if (!writeIndentationTrim(node->value->name, mode)) {
						return false;
					};
					break;
				case XMLNodeType::Element:
					if (!write("<")) {
						return false;
					};
					if (!write(node->value->name)) {
						return false;
					};
					if (node->value->attributes) {
						if (node->value->attributes->length() > 0) {
							for (int index = 0; index < node->value->attributes->length(); ++index) {
								TPointer<typename XMLDocument::Attribute> &attribute_((*node->value->attributes)[index]);
								if (attribute_) {
									if (!write("\x20")) {
										return false;
									};
									if (!write(attribute_->name)) {
										return false;
									};
									if (!write("=\"")) {
										return false;
									};
									if (!write(attribute_->value)) {
										return false;
									};
									if (!write("\"")) {
										return false;
									};
								};
							};
						};
					};
					if (node->value->branch) {
						if (node->value->branch->isEmpty()) {
							if (!write("\x20")) {
								return false;
							};
							if (!write("/>")) {
								return false;
							};
							break;
						};

						if (!write(">")) {
							return false;
						};

						XMLDocument branch(node->value->branch);

						if (indentationIsContentBranch(branch, mode)) {
							if (!write(branch, XMLParserMode::Trim, 0)) {
								return false;
							};
						} else {

							if (!writeIndentationEnd(mode)) {
								return false;
							};

							if (!write(branch, mode, level + 1)) {
								return false;
							};

							if (!writeIndentationBegin(mode, level)) {
								return false;
							};
						};

						if (!write("</")) {
							return false;
						};

						if (!write(node->value->name)) {
							return false;
						};

						if (!write(">")) {
							return false;
						};

						break;
					};

					if (!write("\x20")) {
						return false;
					};
					if (!write("/>")) {
						return false;
					};

					break;
				default:
					break;
				};

				if (!writeIndentationEnd(mode)) {
					return false;
				};
			};
			return true;
		};

		bool XMLWriter::save(XMLDocument &xml, const char *fileName, int mode) {
			XMLWriter xmlWriter;
			File file;
			if (file.openWrite(fileName)) {
				if (xmlWriter.open(&file)) {
					return xmlWriter.write(xml, mode);
				};
			};
			return false;
		};

	};
};
