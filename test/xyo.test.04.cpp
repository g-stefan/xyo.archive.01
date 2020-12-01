// Public domain
// http://unlicense.org/
// Created by Grigore Stefan <g_stefan@yahoo.com>

#include "xyo.hpp"

namespace Main {

	using namespace XYO;

	class Application :
		public virtual IMain {
			XYO_DISALLOW_COPY_ASSIGN_MOVE(Application);
		public:

			inline Application() {
			};

			void test();
			int main(int cmdN, char *cmdS[]);
	};

	void Application::test() {
		JSON::initMemory();
		TPointer<JSON::Value> jsonObject;
		String jsonString;
		String toCheck;

		//---
		toCheck = "[\"1\",\"2\",\"3\"]";
		jsonObject = JSON::decode(toCheck);
		if(!jsonObject) {
			throw(Error("#1"));
		};
		jsonString = JSON::encode(jsonObject);
		if(jsonString != toCheck) {
			throw(Error("#2"));
		};
		printf("%s\n", jsonString.value());

		//---
		toCheck = "{\"1\":\"a\",\"2\":\"b\",\"3\":\"c\"}";
		jsonObject = JSON::decode(toCheck);
		if(!jsonObject) {
			throw(Error("#3"));
		};
		jsonString = JSON::encode(jsonObject);
		if(jsonString != toCheck) {
			throw(Error("#4"));
		};
		printf("%s\n", jsonString.value());

		//---
		toCheck = "[{\"1\":\"a\",\"2\":[\"a\",\"b\",\"c\"],\"3\":\"c\"},null,123,123.45,-1.23,\"hello\"]";
		jsonObject = JSON::decode(toCheck);
		if(!jsonObject) {
			throw(Error("#5"));
		};
		jsonString = JSON::encode(jsonObject);
		if(jsonString != toCheck) {
			throw(Error("#6"));
		};
		printf("%s\n", jsonString.value());
		//---
		jsonString = JSON::encodeWithIndentation(jsonObject);
		printf("%s\n", jsonString.value());
		jsonObject = JSON::decode(jsonString);
		if(!jsonObject) {
			throw(Error("#7"));
		};
		jsonString = JSON::encode(jsonObject);
		if(jsonString != toCheck) {
			throw(Error("#8"));
		};
		//---


		//---
		toCheck = "[{\"1\":\"x\",\"2\":[\"y\",\"z\",\"k\"],\"3\":\"c\"},null,123,123.45,-1.23,\"hello\"]";
		jsonObject = JSON::decode(toCheck);
		if(!jsonObject) {
			throw(Error("#9"));
		};
		jsonString = JSON::encode(jsonObject);
		if(jsonString != toCheck) {
			throw(Error("#10"));
		};
		printf("%s\n", jsonString.value());
		//---
		jsonString = JSON::encodeWithIndentation(jsonObject);
		printf("%s\n", jsonString.value());
		jsonObject = JSON::decode(jsonString);
		if(!jsonObject) {
			throw(Error("#11"));
		};
		jsonString = JSON::encode(jsonObject);
		if(jsonString != toCheck) {
			throw(Error("#12"));
		};
		//---
	};

	int Application::main(int cmdN, char *cmdS[]) {
		uint64_t beginTimestampInMilliseconds;
		uint64_t endTimestampInMilliseconds;
		uint64_t intervalTimestampInMilliseconds;
		int retV;

		retV=0;
		printf("-> xyo.test.04\n");

		try {
			beginTimestampInMilliseconds = DateTime::timestampInMilliseconds();

			// ---

			test();

			// ---

			endTimestampInMilliseconds = DateTime::timestampInMilliseconds();
			intervalTimestampInMilliseconds = endTimestampInMilliseconds - beginTimestampInMilliseconds;

			printf("-> execution time: " XYO_FORMAT_SIZET " ms\n", (size_t)intervalTimestampInMilliseconds);
		} catch(const Error &e) {
			printf("Error: %s\n", ((const_cast<Error &>(e)).getMessage()).value());
			retV=1;
		} catch (const std::exception &e) {
			printf("Error: %s\n", e.what());
			retV=1;
		} catch (...) {
			printf("Error: Unknown\n");
			retV=1;
		};

		return retV;
	};

};

XYO_APPLICATION_MAIN_STD(Main::Application);
