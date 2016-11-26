#include "WindowPrinter.h"
#include <stdexcept>

WindowPrinter::WindowPrinter(HWND windowHandle) :
	windowHandle(windowHandle)
{
	if (windowHandle == nullptr)
		throw std::invalid_argument("Handle to window must not be null");
}

std::shared_ptr<CImage> WindowPrinter::PrintWindow()
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

void WindowPrinter::PrintAndSaveToFile(std::string filePath)
{
	auto print = PrintWindow();
	print->Save(filePath.c_str());
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
