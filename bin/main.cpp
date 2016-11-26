#include <Windows.h>
#include <string>
#include <iostream>
#include <cpplocate/cpplocate.h>
#include "WindowPrinter.h"

int main(int argc, char* argv[])
{
	using namespace std;
	std::string processName = "Minesweeper";
	HWND hwnd = FindWindow(processName.c_str(), NULL);    //the window can't be min
	if (hwnd == NULL)
	{
		cout << "Can't find window: " << processName << endl;
		return 0;
	}

	auto windowPrinter = WindowPrinter(hwnd);
	auto filePath = cpplocate::getModulePath() + "/" + "test.jpg";
	windowPrinter.PrintAndSaveToFile(filePath);
	
	cout << "Printed to file!" << endl;

	return 0;
}