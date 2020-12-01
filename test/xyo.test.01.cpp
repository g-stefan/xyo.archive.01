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

			int mandelbrot(double x, double y);
			void test();

			int main(int cmdN, char *cmdS[]);
	};

	int Application::mandelbrot(double x0, double y0) {
		double x = 0;
		double y = 0;
		double xTemp;
		int iteration = 0;
		int maxIteration = 1000;
		while ((x * x + y * y < 2 * 2) && (iteration < maxIteration)) {
			xTemp = x * x - y * y + x0;
			y = 2 * x * y + y0;
			x = xTemp;
			++iteration;
		};
		return iteration;
	};

	void Application::test() {
		String output;
		String map;

		double x, y;
		int z;

		map += " ";
		for(z = 0; z < 180; ++z) {
			map += ".";
		};
		map += "#";

		for(y = -20; y < 20; ++y) {
			for(x = -80; x < 80; ++x) {
				output += map[((mandelbrot(x / 50, y / 25) * (map.length() - 1)) / 1000)];
			};
			output += "\n";
		};
		printf("%s\n", output.value());
	};

	int Application::main(int cmdN, char *cmdS[]) {
		uint64_t beginTimestampInMilliseconds;
		uint64_t endTimestampInMilliseconds;
		uint64_t intervalTimestampInMilliseconds;
		int retV;

		retV=0;
		printf("-> xyo.test.01\n");

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
