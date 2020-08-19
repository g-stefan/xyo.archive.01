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
		File utfFile;
		Utf8Write utf8Write;
		Utf8Read utf8Read;
		String utfData;
		bool isOk;

		isOk=false;
		if(utfFile.openWrite("utf.test.02.01.bin")) {
			if(utf8Write.open(&utfFile, UtfStreamMode::Utf8)) {
				StreamX::write(utf8Write, "\xEF\xBB\xBF");
				StreamX::writeLn(utf8Write, "Hello World");
				isOk=true;
			};
			utf8Write.close();
			utfFile.close();
		};

		if(!isOk){
			throw(Error("Unable to write utf.test.02.01.bin"));			
		};

		isOk=false;
		if(utfFile.openWrite("utf.test.02.02.bin")) {
			if(utf8Write.open(&utfFile, UtfStreamMode::Utf16)) {
				StreamX::write(utf8Write, "\xEF\xBB\xBF");
				StreamX::writeLn(utf8Write, "Hello World");
				isOk=true;
			};
			utf8Write.close();
			utfFile.close();			
		};

		if(!isOk){
			throw(Error("Unable to write utf.test.02.02.bin"));			
		};

		isOk=false;
		if(utfFile.openWrite("utf.test.02.03.bin")) {
			if(utf8Write.open(&utfFile, UtfStreamMode::Utf32)) {
				StreamX::write(utf8Write, "\xEF\xBB\xBF");
				StreamX::writeLn(utf8Write, "Hello World");
				isOk=true;
			};
			utf8Write.close();
			utfFile.close();
		};

		if(!isOk){
			throw(Error("Unable to write utf.test.02.03.bin"));
		};

		//---

		isOk=false;
		if(utfFile.openRead("utf.test.02.01.bin")) {
			if(utf8Read.open(&utfFile, UtfStreamMode::Utf8)) {
				isOk=true;
				if(!StreamX::readLn(utf8Read, utfData, 1024)) {
					throw(Error("#1"));
				};
				if(utfData != "\xEF\xBB\xBFHello World\x0D\x0A") {
					throw(Error("#2"));
				};
			};
			utf8Read.close();
			utfFile.close();
		};

		if(!isOk){
			throw(Error("Unable to read utf.test.02.01.bin"));
		};

		isOk=false;
		if(utfFile.openRead("utf.test.02.02.bin")) {
			if(utf8Read.open(&utfFile, UtfStreamMode::Utf16)) {
				isOk=true;
				if(!StreamX::readLn(utf8Read, utfData, 1024)) {
					throw(Error("#3"));
				};
				if(utfData != "\xEF\xBB\xBFHello World\x0D\x0A") {
					throw(Error("#4"));
				};
			};
			utf8Read.close();
			utfFile.close();
		};

		if(!isOk){
			throw(Error("Unable to read utf.test.02.02.bin"));
		};

		isOk=false;
		if(utfFile.openRead("utf.test.02.03.bin")) {
			if(utf8Read.open(&utfFile, UtfStreamMode::Utf32)) {
				isOk=true;
				if(!StreamX::readLn(utf8Read, utfData, 1024)) {
					throw(Error("#5"));
				};
				if(utfData != "\xEF\xBB\xBFHello World\x0D\x0A") {
					throw(Error("#6"));
				};
			};
			utf8Read.close();
			utfFile.close();
		};

		if(!isOk){
			throw(Error("Unable to read utf.test.02.03.bin"));
		};
	};

	int Application::main(int cmdN, char *cmdS[]) {
		uint64_t beginTimestampInMilliseconds;
		uint64_t endTimestampInMilliseconds;
		uint64_t intervalTimestampInMilliseconds;
		int retV;

		retV=0;
		printf("-> xyo.test.03\n");

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
