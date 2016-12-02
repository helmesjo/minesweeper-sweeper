#include "WindowDriver.h"
#include <stdexcept>

using namespace helmesjo;

WindowDriver::WindowDriver(const std::string& processName)
{
	// Do we have to release the handle..?
	windowHandle = FindWindow(processName.c_str(), NULL);    //the window can't be min
	if (windowHandle == nullptr)
		throw std::invalid_argument("Could not find window with name: " + processName);
}

std::shared_ptr<CImage> WindowDriver::printWindow()
{
	auto imageDeleter = [](CImage* img) { 
		img->ReleaseDC();
		delete img;
	};
	auto print = std::shared_ptr<CImage>(new CImage(), imageDeleter);

	RECT rect = { 0 };
	GetWindowRect(windowHandle, &rect);
	print->Create(rect.right - rect.left, rect.bottom - rect.top, 32);
	HDC device_context_handle = print->GetDC();
	::PrintWindow(windowHandle, device_context_handle, PW_CLIENTONLY);

	return print;
}

void WindowDriver::PrintAndSaveToFile(const std::string& filePath)
{
	auto print = printWindow();
	print->Save(filePath.c_str());
}

bool helmesjo::WindowDriver::sendInput(InputData inputObject)
{
	return false;
}

/*
	//copy to clipboard
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hbmp);
	CloseClipboard();

	//release
	DeleteDC(hdc);
	DeleteObject(hbmp);
	ReleaseDC(NULL, hdcScreen);

	cout << "success copy to clipboard, please paste it to the 'mspaint'" << endl;

	return 0;
	*/
