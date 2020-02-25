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
			printf("#Error #1\r\n");
		};
		jsonString = JSON::encode(jsonObject);
		if(jsonString != toCheck) {
			printf("#Error #1 - encoding\r\n");
		};
		printf("%s\n", jsonString.value());

		//---
		toCheck = "{\"1\":\"a\",\"2\":\"b\",\"3\":\"c\"}";
		jsonObject = JSON::decode(toCheck);
		if(!jsonObject) {
			printf("#Error #2\r\n");
		};
		jsonString = JSON::encode(jsonObject);
		if(jsonString != toCheck) {
			printf("#Error #2 - encoding\r\n");
		};
		printf("%s\n", jsonString.value());

		//---
		toCheck = "[{\"1\":\"a\",\"2\":[\"a\",\"b\",\"c\"],\"3\":\"c\"},null,123,123.45,-1.23,\"hello\"]";
		jsonObject = JSON::decode(toCheck);
		if(!jsonObject) {
			printf("#Error #3\r\n");
		};
		jsonString = JSON::encode(jsonObject);
		if(jsonString != toCheck) {
			printf("#Error #3 - encoding\r\n");
		};
		printf("%s\n", jsonString.value());
		//---
		jsonString = JSON::encodeWithIndentation(jsonObject);
		printf("%s\n", jsonString.value());
		jsonObject = JSON::decode(jsonString);
		if(!jsonObject) {
			printf("#Error #4\r\n");
		};
		jsonString = JSON::encode(jsonObject);
		if(jsonString != toCheck) {
			printf("#Error #4 - encoding\r\n");
		};
		//---


		//---
		toCheck = "[{\"1\":\"x\",\"2\":[\"y\",\"z\",\"k\"],\"3\":\"c\"},null,123,123.45,-1.23,\"hello\"]";
		jsonObject = JSON::decode(toCheck);
		if(!jsonObject) {
			printf("#Error #5\r\n");
		};
		jsonString = JSON::encode(jsonObject);
		if(jsonString != toCheck) {
			printf("#Error #5 - encoding\r\n");
		};
		printf("%s\n", jsonString.value());
		//---
		jsonString = JSON::encodeWithIndentation(jsonObject);
		printf("%s\n", jsonString.value());
		jsonObject = JSON::decode(jsonString);
		if(!jsonObject) {
			printf("#Error #6\r\n");
		};
		jsonString = JSON::encode(jsonObject);
		if(jsonString != toCheck) {
			printf("#Error #6 - encoding\r\n");
		};
		//---
	};

	int Application::main(int cmdN, char *cmdS[]) {
		uint64_t beginTimestampInMilliseconds;
		uint64_t endTimestampInMilliseconds;
		uint64_t intervalTimestampInMilliseconds;

		printf("-> xyo.test.04\n");

		beginTimestampInMilliseconds = DateTime::timestampInMilliseconds();

		// ---

		test();

		// ---

		endTimestampInMilliseconds = DateTime::timestampInMilliseconds();
		intervalTimestampInMilliseconds = endTimestampInMilliseconds - beginTimestampInMilliseconds;

		printf("-> execution time: " XYO_FORMAT_SIZET " ms\n", (size_t)intervalTimestampInMilliseconds);

		return 0;
	};

};

XYO_APPLICATION_MAIN_STD(Main::Application);
