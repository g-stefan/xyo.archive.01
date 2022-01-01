//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_MULTITHREADING_TATOMIC_HPP
#define XYO_MULTITHREADING_TATOMIC_HPP

#ifndef XYO__DEPENDENCY_HPP
#include "xyo--dependency.hpp"
#endif

#ifdef XYO_MULTI_THREAD
namespace XYO {
	namespace Multithreading {

		template<typename T>
		class TAtomic {
			protected:

				std::atomic<T> value;

			public:

				static const bool isAtomic = true;

				inline TAtomic() {
				};

				inline void set(const T &value_) {
					value.store(value_, std::memory_order_relaxed);
				};

				inline void set(T &&value_) {
					value.store(value_, std::memory_order_relaxed);
				};

				inline T get() const {
					return value.load(std::memory_order_relaxed);
				};

				inline TAtomic(const TAtomic &value_) {
					set(value_.get());
				};

				inline TAtomic(TAtomic &&value_) {
					set(value_.get());
				};

				inline TAtomic &operator =(const TAtomic &value_) {
					set(value_.get());
				};

				inline TAtomic &operator =(TAtomic &&value_) {
					set(value_.get());
				};

				inline TAtomic(const T &value_) {
					set(value_);
				};

				inline TAtomic(T &&value_) {
					set(value_);
				};

				inline TAtomic &operator =(const T &value_) {
					set(value_);
					return *this;
				};

				inline TAtomic &operator =(T &&value_) {
					set(value_);
					return *this;
				};

				inline operator T() const {
					return get();
				};
		};
	};
};
#endif

#ifdef XYO_SINGLE_THREAD
namespace XYO {
	namespace Multithreading {

		template<typename T>
		class TAtomic {
			protected:

				T value;

			public:

				static const bool isAtomic = false;

				inline TAtomic() {
				};

				inline void set(const T &value_) {
					value = value_;
				};

				inline void set(T &&value_) {
					value = std::move(value_);
				};

				inline T get() const {
					return value;
				};

				inline TAtomic(const TAtomic &value_) {
					set(value_.get());
				};

				inline TAtomic(TAtomic &&value_) {
					set(value_.get());
				};

				inline TAtomic &operator =(const TAtomic &value_) {
					set(value_.get());
				};

				inline TAtomic &operator =(TAtomic &&value_) {
					set(value_.get());
				};

				inline TAtomic(const T &value_) {
					set(value_);
				};

				inline TAtomic(T &&value_) {
					set(value_);
				};

				inline TAtomic &operator =(const T &value_) {
					set(value_);
					return *this;
				};

				inline TAtomic &operator =(T &&value_) {
					set(value_);
					return *this;
				};

				inline operator T() const {
					return get();
				};
		};
	};
};
#endif

#endif

