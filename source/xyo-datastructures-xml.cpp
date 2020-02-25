//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-datastructures-xml.hpp"

namespace XYO {
	namespace DataStructures {
		using namespace XYO::ManagedMemory;


		void XMLDocument::addDocument(XMLDocument &document) {
			if(document) {
				if(!root) {
					root.newMemory();
				};
				typename Branch::Node *index;
				for(index = document.root->head; index != nullptr; index = index->next) {
					root->pushToTail(index->value);
				};
			};
		};

		XMLDocument XMLDocument::get(const char *name) {
			typename Branch::Node *scan;
			XMLDocument retV;
			if(!root) {
				return retV;
			};

			for(scan = root->head; scan != nullptr; scan = scan->next) {
				if(scan->value->type == XMLNodeType::Element) {
					if(scan->value->name == name) {
						if(!retV.root) {
							retV.root.newMemory();
						};
						retV.root->pushToTail(scan->value);
					};
				};
			};

			return retV;
		};

		XMLDocument XMLDocument::find(const char *name) {
			typename Branch::Node *scan;
			XMLDocument retV;
			if(!root) {
				return retV;
			};

			for(scan = root->head; scan != nullptr; scan = scan->next) {
				if(scan->value->type == XMLNodeType::Element) {
					if(scan->value->name == name) {
						if(!retV.root) {
							retV.root.newMemory();
						};
						retV.root->pushToTail(scan->value);
					};

					if(scan->value->branch) {
						XMLDocument tmp(scan->value->branch);
						XMLDocument list = tmp.find(name);
						if(list) {
							if(!retV.root) {
								retV.root.newMemory();
							};
							typename Branch::Node *index;
							for(index = list.root->head; index != nullptr; index = index->next) {
								retV.root->pushToTail(index->value);
							};
						};
					};
				};
			};

			return retV;
		};

		XMLDocument XMLDocument::findWithAttributeValue(const char *name, const char *attribute, const char *value) {
			typename Branch::Node *scan;

			XMLDocument retV;
			if(!root) {
				return retV;
			};

			for(scan = root->head; scan != nullptr; scan = scan->next) {
				if(scan->value->type == XMLNodeType::Element) {

					if(scan->value->name == name) {
						size_t index;
						for(index = 0; index < scan->value->attributes->length(); ++index) {
							TPointer<XMLAttribute> &attribute_(scan->value->attributes->index(index));
							if(attribute_) {
								if(attribute_->name == attribute) {
									if(attribute_->value == value) {
										if(!retV.root) {
											retV.root.newMemory();
										};
										retV.root->pushToTail(scan->value);
									};
								};
							};
						};
					};

					if(scan->value->branch) {
						XMLDocument tmp(scan->value->branch);
						XMLDocument list = tmp.findWithAttributeValue(name, attribute, value);
						if(list) {
							if(!retV.root) {
								retV.root.newMemory();
							};
							typename Branch::Node *index;
							for(index = list.root->head; index != nullptr; index = index->next) {
								retV.root->pushToTail(index->value);
							};
						};
					};
				};
			};

			return retV;
		};

		size_t XMLDocument::length() {

			if(!root) {
				return 0;
			};

			size_t retV;
			typename Branch::Node *scan;
			retV = 0;
			for(scan = root->head; scan != nullptr; scan = scan->next) {
				++retV;
			};
			return retV;
		};

		TPointer<XMLNode> XMLDocument::getIndex(size_t index_) {
			typename Branch::Node *scan;
			size_t count_ = 0;
			for(scan = root->head; scan != nullptr; scan = scan->next, ++count_) {
				if(count_ == index_) {
					return scan->value;
				};
			};
			return nullptr;
		};

		void XMLDocument::setIndex(size_t index_, Node *node) {
			typename Branch::Node *scan;
			size_t count_ = 0;
			for(scan = root->head; scan != nullptr; scan = scan->next, ++count_) {
				if(count_ == index_) {
					scan->value = node;
					break;
				};
			};
		};

		void XMLDocument::removeIndex(size_t index_) {
			typename Branch::Node *scan;
			size_t count_ = 0;
			for(scan = root->head; scan != nullptr; scan = scan->next, ++count_) {
				if(count_ == index_) {
					root->extractNode(scan);
					Branch::deleteNode(scan);
					break;
				};
			};
		};
	};
};



