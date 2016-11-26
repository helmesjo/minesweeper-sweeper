#include <Windows.h>
#include <string>
#include <iostream>
#include <cpplocate/cpplocate.h>
#include "WindowPrinter.h"
#include <chrono>

int main(int argc, char* argv[])
{
	using namespace std;
	using std::chrono::high_resolution_clock;
	using std::chrono::milliseconds;

	auto processName = "Minesweeper"s;
	HWND hwnd = FindWindow(processName.c_str(), NULL);    //the window can't be min
	if (hwnd == NULL)
	{
		cout << "Can't find window: " << processName << endl;
		return 0;
	}

	auto clock = chrono::high_resolution_clock();
	auto start = clock.now();

	auto windowPrinter = WindowPrinter(hwnd);
	for (auto i = 0u; i < 1000; i++)
		windowPrinter.PrintWindow();

	auto elapsed = std::chrono::duration_cast<milliseconds>(high_resolution_clock::now() - start);
	cout << "Elapsed time: " << elapsed.count() << endl;

	//auto filePath = cpplocate::getModulePath() + "/" + "test.jpg";
	//windowPrinter.PrintAndSaveToFile(filePath);
	//cout << "Printed to file!" << endl;

	return 0;
}