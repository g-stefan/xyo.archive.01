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
			throw(Error("#1"));
		};

		variable = static_cast<Value *>(&vNumber);
		if(!TIsType<VNumber>(variable)) {
			throw(Error("#2"));
		};

		variable = static_cast<Value *>(&vString);
		if(!TIsType<VString>(variable)) {
			throw(Error("#3"));
		};

		variable = static_cast<Value *>(&vArray);
		if(!TIsType<VArray>(variable)) {
			throw(Error("#4"));
		};

		variable = static_cast<Value *>(&vAssociativeArray);
		if(!TIsType<VAssociativeArray>(variable)) {
			throw(Error("#5"));
		};
		if(TIsType<VNull>(variable)) {
			throw(Error("#6"));
		};
		if(TIsType<VArray>(variable)) {
			throw(Error("#7"));
		};
		if(!TIsType<Value>(variable)) {
			throw(Error("#8"));
		};
		VAssociativeArray *vObject = TDynamicCast<VAssociativeArray *>(variable);
		if(vObject == nullptr) {
			throw(Error("#9"));
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
		int retV;

		retV=0;
		printf("-> xyo.test.02\n");

		try {

			beginTimestampInMilliseconds = DateTime::timestampInMilliseconds();

			// ---

			test();

			// ---

			endTimestampInMilliseconds = DateTime::timestampInMilliseconds();
			intervalTimestampInMilliseconds = endTimestampInMilliseconds - beginTimestampInMilliseconds;

			printf("-> execution time: " XYO_FORMAT_SIZET " ms\n", (size_t)intervalTimestampInMilliseconds);

		} catch(const Error &e) {
			printf("Error: %s\n",((const_cast<Error &>(e)).getMessage()).value());			
			retV=1;
		} catch (const std::exception &e) {
			printf("Error: %s\n",e.what());
			retV=1;
		} catch (...) {
			printf("Error: Unknown\n");
			retV=1;
		};

		return retV;
	};

};

XYO_APPLICATION_MAIN_STD(Main::Application);
