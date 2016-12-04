#include "WindowDriver.h"
#include "Image.h"

#include <atlimage.h>
#include <stdexcept>
#include <Gdiplusimaging.h>
#include <cpplocate/cpplocate.h>

using namespace helmesjo;

#define SCREEN_WIDTH (::GetSystemMetrics( SM_CXSCREEN )-1) 
#define SCREEN_HEIGHT (::GetSystemMetrics( SM_CYSCREEN )-1) 

static void inline makeAbsXY(double &x, double &y) {
	x = (x * 0xFFFF) / SCREEN_WIDTH;
	y = (y * 0xFFFF) / SCREEN_HEIGHT;
}

WindowDriver::WindowDriver(const std::string& processName)
{
	// Do we have to release the handle..?
	windowHandle = FindWindow(processName.c_str(), NULL);    //the window can't be min
	if (windowHandle == nullptr)
		throw std::invalid_argument("Could not find window with name: " + processName);
}

std::shared_ptr<Image> WindowDriver::printWindow()
{
	//auto imageDeleter = [](CImage* img) { 
	//	img->ReleaseDC();
	//	delete img;
	//};
	//auto print = std::shared_ptr<CImage>(new CImage(), imageDeleter);

	auto print = CImage();
	RECT rect = { 0 };
	GetWindowRect(windowHandle, &rect);
	auto width = static_cast<size_t>(rect.right - rect.left);
	auto height = static_cast<size_t>(rect.bottom - rect.top);
	print.Create(width, height, 32);
	HDC device_context_handle = print.GetDC();
	::PrintWindow(windowHandle, device_context_handle, PW_CLIENTONLY);

	auto path = cpplocate::getModulePath() + "/tmp.bmp";
	print.Save(path.c_str(), Gdiplus::ImageFormatBMP);

	print.ReleaseDC();

	return std::make_shared<Image>(path);
}

void WindowDriver::PrintAndSaveToFile(const std::string& filePath)
{
	auto print = printWindow();
	print->saveToPath(filePath);
	//print->Save(filePath.c_str());
}

INPUT MouseSetup(unsigned int x, unsigned int y)
{
	INPUT ip;
	ip.type = INPUT_MOUSE;
	ip.mi.dx = x * (0xFFFF / SCREEN_WIDTH);
	ip.mi.dy = y * (0xFFFF / SCREEN_HEIGHT);
	ip.mi.mouseData = 0;
	ip.mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
	ip.mi.time = 0;
	ip.mi.dwExtraInfo = 0;
	return ip;
}

POINT calculateXY(HWND windowHandle, unsigned int* x, unsigned int* y) {
	SetForegroundWindow(windowHandle);
	// Assume mouse-click for now (fix later)
	RECT rect;
	GetWindowRect(windowHandle, &rect);

	POINT pt = { static_cast<LONG>(*x), static_cast<LONG>(*y) };
	ClientToScreen(windowHandle, &pt);

	return pt;
}

void helmesjo::WindowDriver::sendLeftClick(unsigned int x, unsigned int y)
{
	POINT pt = calculateXY(windowHandle, &x, &y);//{ static_cast<LONG>(x), static_cast<LONG>(y) };

	auto ip = MouseSetup(pt.x, pt.y);
	
	ip.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN);
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(1);

	ip.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
	SendInput(1, &ip, sizeof(INPUT));
}

void helmesjo::WindowDriver::sendRightClick(unsigned int x, unsigned int y)
{
	POINT pt = calculateXY(windowHandle, &x, &y);//{ static_cast<LONG>(x), static_cast<LONG>(y) };

	auto ip = MouseSetup(pt.x, pt.y);

	ip.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_RIGHTDOWN);
	SendInput(1, &ip, sizeof(INPUT));

	Sleep(1);

	ip.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTUP);
	SendInput(1, &ip, sizeof(INPUT));
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
