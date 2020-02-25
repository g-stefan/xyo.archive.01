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

		if(utfFile.openWrite("utf.test.02.01.bin")) {
			if(utf8Write.open(&utfFile, UtfStreamMode::Utf8)) {
				StreamX::write(utf8Write, "\xEF\xBB\xBF");
				StreamX::writeLn(utf8Write, "Hello World");
			};
			utf8Write.close();
			utfFile.close();
		};

		if(utfFile.openWrite("utf.test.02.02.bin")) {
			if(utf8Write.open(&utfFile, UtfStreamMode::Utf16)) {
				StreamX::write(utf8Write, "\xEF\xBB\xBF");
				StreamX::writeLn(utf8Write, "Hello World");
			};
			utf8Write.close();
			utfFile.close();
		};

		if(utfFile.openWrite("utf.test.02.03.bin")) {
			if(utf8Write.open(&utfFile, UtfStreamMode::Utf32)) {
				StreamX::write(utf8Write, "\xEF\xBB\xBF");
				StreamX::writeLn(utf8Write, "Hello World");
			};
			utf8Write.close();
			utfFile.close();
		};

		//---

		if(utfFile.openRead("utf.test.02.01.bin")) {
			if(utf8Read.open(&utfFile, UtfStreamMode::Utf8)) {
				if(!StreamX::readLn(utf8Read, utfData, 1024)) {
					printf("#Error #1\r\n");
				};
				if(utfData != "\xEF\xBB\xBFHello World\x0D\x0A") {
					printf("#Error #1 - check");
				};
			};
			utf8Read.close();
			utfFile.close();
		};

		if(utfFile.openRead("utf.test.02.02.bin")) {
			if(utf8Read.open(&utfFile, UtfStreamMode::Utf16)) {
				if(!StreamX::readLn(utf8Read, utfData, 1024)) {
					printf("#Error #2\r\n");
				};
				if(utfData != "\xEF\xBB\xBFHello World\x0D\x0A") {
					printf("#Error #2 - check");
				};
			};
			utf8Read.close();
			utfFile.close();
		};

		if(utfFile.openRead("utf.test.02.03.bin")) {
			if(utf8Read.open(&utfFile, UtfStreamMode::Utf32)) {
				if(!StreamX::readLn(utf8Read, utfData, 1024)) {
					printf("#Error #3\r\n");
				};
				if(utfData != "\xEF\xBB\xBFHello World\x0D\x0A") {
					printf("#Error #3 - check");
				};
			};
			utf8Read.close();
			utfFile.close();
		};
	};

	int Application::main(int cmdN, char *cmdS[]) {
		uint64_t beginTimestampInMilliseconds;
		uint64_t endTimestampInMilliseconds;
		uint64_t intervalTimestampInMilliseconds;

		printf("-> xyo.test.03\n");

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
