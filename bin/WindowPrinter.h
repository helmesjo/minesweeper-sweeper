#pragma once

#include <atlimage.h>
#include <Windows.h>
#include <string>
#include <memory>

class WindowPrinter {

public:
	WindowPrinter(HWND windowHandle);

	std::shared_ptr<ATL::CImage> PrintWindow();
	void PrintAndSaveToFile(std::string filePath);

private:
	HWND windowHandle;
};