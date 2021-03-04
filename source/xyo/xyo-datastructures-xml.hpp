//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_DATASTRUCTURES_XML_HPP
#define XYO_DATASTRUCTURES_XML_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#include "xyo-managedmemory-tmemory.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TDOUBLEENDEDQUEUE_HPP
#include "xyo-datastructures-tdoubleendedqueue.hpp"
#endif

#ifndef XYO_ENCODING_STRING_HPP
#include "xyo-encoding-string.hpp"
#endif

#ifndef XYO_DATASTRUCTURES_TDYNAMICARRAY_HPP
#include "xyo-datastructures-tdynamicarray.hpp"
#endif

namespace XYO {
	namespace DataStructures {
		using namespace XYO::ManagedMemory;
		using namespace XYO::Encoding;

		class XMLAttribute: public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(XMLAttribute);
			public:

				String name;
				String value;

				inline XMLAttribute() {
				};

				inline ~XMLAttribute() {
				};

				static inline void initMemory() {
					String::initMemory();
				};

				inline void activeDestructor() {
					name.activeDestructor();
					value.activeDestructor();
				};
		};

	};

	namespace ManagedMemory {
		template<>
		struct TMemory<DataStructures::XMLAttribute> : TMemoryPoolActive<DataStructures::XMLAttribute> {};
	};

	namespace DataStructures {

		struct XMLNodeType {
			enum {
				None = 0,
				Element = 1,
				Content = 2,
				CDATA = 3,
				Comment = 4,
				Declaration = 5,
				Bom = 6,
				DocumentTypeDefinition = 7
			};
		};

		class XMLNode : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(XMLNode);
			public:

				typedef XMLAttribute Attribute;
				typedef TDynamicArray<TPointer<Attribute>, 3> Attributes;
				typedef TDoubleEndedQueue<TPointerX<XMLNode> > Branch;

				uint16_t type;
				String name;
				TPointer<Attributes> attributes;
				TPointerX<Branch> branch;

				inline XMLNode() {
					branch.pointerLink(this);
					type = XMLNodeType::None;
				};

				inline ~XMLNode() {
				};

				inline void activeDestructor() {
					attributes.activeDestructor();
					name.activeDestructor();
					type = XMLNodeType::None;
				};

				static inline void initMemory() {
					String::initMemory();
					TPointer<TDynamicArray<XMLAttribute> >::initMemory();
				};
		};

	};

	namespace ManagedMemory {
		template<>
		struct TMemory<DataStructures::XMLNode> : TMemoryPoolActive<DataStructures::XMLNode> {};
	};

	namespace DataStructures {

		struct XMLDocument : Object {
			typedef XMLNode Node;
			typedef typename Node::Branch Branch;
			typedef typename Node::Attribute Attribute;
			typedef typename Node::Attributes Attributes;

			static inline Node *newNode() {
				return TMemory<Node>::newMemory();
			};

			static inline void deleteNode(Node *this_) {
				return TMemory<Node>::deleteMemory(this_);
			};

			static inline void initMemory() {
				TMemory<Node>::initMemory();
			};

			TPointerX<Branch> root;

			inline XMLDocument() {
				root.pointerLink(this);
			};

			inline ~XMLDocument() {
			};

			inline XMLDocument(const Branch *root_) {
				root.pointerLink(this);
				root = root_;
			};

			inline XMLDocument(const TPointerX<Branch> &root_) {
				root.pointerLink(this);
				root = root_;
			};

			inline XMLDocument(const XMLDocument &value) {
				root.pointerLink(this);
				root = (const_cast<XMLDocument &>(value)).root;
			};

			inline XMLDocument(XMLDocument &&value) {
				root.pointerLink(this);
				root = std::move(value.root);
			};

			inline XMLDocument &operator=(const Branch *root_) {
				root = root_;
				return *this;
			};

			inline XMLDocument &operator=(const XMLDocument &value) {
				root = (const_cast<XMLDocument &>(value)).root;
				return *this;
			};

			inline XMLDocument &operator=(XMLDocument &&value) {
				root = std::move(value.root);
				return *this;
			};

			inline void empty() {
				root.deleteMemory();
			};

			inline void activeDestructor() {
				empty();
			};

			inline operator bool() const {
				return root;
			};

			inline XMLDocument add(Node *node) {
				if(!root) {
					root.newMemory();
				};
				if(!(node->branch)) {
					node->branch.newMemory();
				};
				root->pushToTail(node);
				return node->branch;
			};

			XYO_EXPORT void addDocument(XMLDocument &document);
			XYO_EXPORT XMLDocument get(const char *name);
			XYO_EXPORT XMLDocument find(const char *name);
			XYO_EXPORT XMLDocument findWithAttributeValue(const char *name, const char *attribute, const char *value);
			XYO_EXPORT size_t length();
			XYO_EXPORT TPointer<Node> getIndex(size_t index_);
			XYO_EXPORT void setIndex(size_t index_, Node *node);
			XYO_EXPORT void removeIndex(size_t index_);
		};

	};

	namespace ManagedMemory {
		template<>
		struct TMemory<DataStructures::XMLDocument> : TMemoryPoolActive<DataStructures::XMLDocument> {};
	};

};

#endif

