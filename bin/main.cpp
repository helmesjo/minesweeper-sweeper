#include <string>
#include <iostream>
#include <cpplocate/cpplocate.h>
#include "WindowDriver.h"
#include <chrono>

using namespace helmesjo;

int main(int argc, char* argv[])
{
	using namespace std;
	using std::chrono::high_resolution_clock;
	using std::chrono::milliseconds;

	auto processName = "Minesweeper"s;
	auto windowPrinter = WindowDriver(processName);

	auto clock = chrono::high_resolution_clock();
	auto start = clock.now();

	//for (auto i = 0u; i < 1000; i++)
	//	windowPrinter.PrintWindow();

	auto elapsed = std::chrono::duration_cast<milliseconds>(high_resolution_clock::now() - start);
	cout << "Elapsed time: " << elapsed.count() << endl;

	auto filePath = cpplocate::getModulePath() + "/" + "test.jpg";
	windowPrinter.PrintAndSaveToFile(filePath);
	//cout << "Printed to file!" << endl;

	return 0;
}