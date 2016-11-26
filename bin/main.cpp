#include <Windows.h>
#include <string>
#include <iostream>
#include <cpplocate/cpplocate.h>
#include "WindowPrinter.h"
#include <chrono>

int main(int argc, char* argv[])
{
	using namespace std;
	typedef std::chrono::high_resolution_clock high_resolution_clock;
	typedef std::chrono::milliseconds milliseconds;

	std::string processName = "Minesweeper";
	HWND hwnd = FindWindow(processName.c_str(), NULL);    //the window can't be min
	if (hwnd == NULL)
	{
		cout << "Can't find window: " << processName << endl;
		return 0;
	}

	chrono::high_resolution_clock clock;
	auto start = clock.now();

	auto windowPrinter = WindowPrinter(hwnd);
	auto filePath = cpplocate::getModulePath() + "/" + "test.jpg";
	for (auto i = 0u; i < 100; i++)
		windowPrinter.PrintWindow();

	auto elapsed = std::chrono::duration_cast<milliseconds>(high_resolution_clock::now() - start);

	cout << "Elapsed time: " << elapsed.count() << endl;

	//windowPrinter.PrintAndSaveToFile(filePath);
	
	cout << "Printed to file!" << endl;

	return 0;
}