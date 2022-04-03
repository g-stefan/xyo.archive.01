//
// XYO
//
// Copyright (c) 2020-2022 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#ifndef XYO_SYSTEM_DATETIME_HPP
#define XYO_SYSTEM_DATETIME_HPP

#ifndef XYO_MANAGEDMEMORY_TMEMORY_HPP
#	include "xyo-managedmemory-tmemory.hpp"
#endif

namespace XYO {
	namespace System {
		using namespace XYO::ManagedMemory;

		class DateTime_;

		class DateTime : public Object {
				XYO_DISALLOW_COPY_ASSIGN_MOVE(DateTime);

			protected:
				DateTime_ *dateTime;

			public:
				XYO_EXPORT DateTime();
				XYO_EXPORT ~DateTime();

				XYO_EXPORT uint16_t getYear();
				XYO_EXPORT uint16_t getMonth();
				XYO_EXPORT uint16_t getDay();
				XYO_EXPORT uint16_t getDayOfWeek();
				XYO_EXPORT uint16_t getHour();
				XYO_EXPORT uint16_t getMinute();
				XYO_EXPORT uint16_t getSecond();
				XYO_EXPORT uint16_t getMilliseconds();
				XYO_EXPORT void setLocalTime();
				XYO_EXPORT void setYear(uint16_t value);
				XYO_EXPORT void setMonth(uint16_t value);
				XYO_EXPORT void setDay(uint16_t value);
				XYO_EXPORT void setDayOfWeek(uint16_t value);
				XYO_EXPORT void setHour(uint16_t value);
				XYO_EXPORT void setMinute(uint16_t value);
				XYO_EXPORT void setSecond(uint16_t value);
				XYO_EXPORT void setMilliseconds(uint16_t value);
				XYO_EXPORT void copy(DateTime &in);
				XYO_EXPORT void plus(DateTime &in);
				XYO_EXPORT void minus(DateTime &in);
				XYO_EXPORT int compare(DateTime &in);
				XYO_EXPORT uint64_t toUnixTime();
				XYO_EXPORT void fromUnixTime(uint64_t);
				XYO_EXPORT static uint64_t timestampInMilliseconds();
		};

	};
};

#endif
