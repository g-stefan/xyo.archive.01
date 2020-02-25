// Public domain
// http://unlicense.org/
// Created by Grigore Stefan <g_stefan@yahoo.com>

#include "xyo.hpp"

namespace Main {

	using namespace XYO;
	using namespace XYO::JSON;

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
		Value *variable;
		VNull vNull;
		VNumber vNumber;
		VString vString;
		VArray vArray;
		VAssociativeArray vAssociativeArray;

		variable = static_cast<Value *>(&vNull);
		if(!TIsType<VNull>(variable)) {
			printf("# Fail 1\n");
		};

		variable = static_cast<Value *>(&vNumber);
		if(!TIsType<VNumber>(variable)) {
			printf("# Fail 2\n");
		};

		variable = static_cast<Value *>(&vString);
		if(!TIsType<VString>(variable)) {
			printf("# Fail 3\n");
		};

		variable = static_cast<Value *>(&vArray);
		if(!TIsType<VArray>(variable)) {
			printf("# Fail 4\n");
		};

		variable = static_cast<Value *>(&vAssociativeArray);
		if(!TIsType<VAssociativeArray>(variable)) {
			printf("# Fail 5\n");
		};
		if(TIsType<VNull>(variable)) {
			printf("# Fail 6\n");
		};
		if(TIsType<VArray>(variable)) {
			printf("# Fail 6\n");
		};
		if(!TIsType<Value>(variable)) {
			printf("# Fail 7\n");
		};
		VAssociativeArray *vObject = TDynamicCast<VAssociativeArray *>(variable);
		if(vObject == nullptr) {
			printf("# Fail 8\n");
		};

		printf("Value: %s\n", TGetTypeKey<Value>());
		printf("VNull: %s - %s\n", TGetTypeKey<VNull>(), vNull.getTypeKey());
		printf("VNumber: %s - %s\n", TGetTypeKey<VNumber>(), vNumber.getTypeKey());
		printf("VString: %s - %s\n", TGetTypeKey<VString>(), vString.getTypeKey());
		printf("VArray: %s - %s\n", TGetTypeKey<VArray>(), vArray.getTypeKey());
		printf("VAssociativeArray: %s - %s\n", TGetTypeKey<VAssociativeArray>(), vAssociativeArray.getTypeKey());

	};

	int Application::main(int cmdN, char *cmdS[]) {
		uint64_t beginTimestampInMilliseconds;
		uint64_t endTimestampInMilliseconds;
		uint64_t intervalTimestampInMilliseconds;

		printf("-> xyo.test.02\n");

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
