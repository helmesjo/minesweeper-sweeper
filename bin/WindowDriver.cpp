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

INPUT MouseSetup(unsigned int x, unsigned int y)
{
	INPUT ip;
	ip.type = INPUT_MOUSE;
	ip.mi.dx = (x * (0xFFFF / GetSystemMetrics(SM_CXSCREEN))) + 1;
	ip.mi.dy = (y * (0xFFFF / GetSystemMetrics(SM_CYSCREEN))) + 1;
	ip.mi.mouseData = 0;
	ip.mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
	ip.mi.time = 0;
	ip.mi.dwExtraInfo = 0;
	return ip;
}

void MouseClick(INPUT ip)
{
	ip.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_MOVE);
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(100);

	ip.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(1000);
}

void helmesjo::WindowDriver::sendInput(InputData inputObject)
{
	SetForegroundWindow(windowHandle);
	// Assume mouse-click for now (fix later)
	RECT rect;
	GetWindowRect(windowHandle, &rect);

	POINT pt = { static_cast<LONG>(inputObject.x), static_cast<LONG>(inputObject.y) };
	ClientToScreen(windowHandle, &pt);

	auto input = MouseSetup(pt.x, pt.y);
	MouseClick(input);
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