#include "WindowPrinter.h"

WindowPrinter::WindowPrinter(HWND windowHandle) noexcept :
	windowHandle(windowHandle)
{
}

std::unique_ptr<CImage> WindowPrinter::PrintWindow()
{
	RECT rect = { 0 };
	GetWindowRect(windowHandle, &rect);
	auto print = std::make_unique<CImage>();
	print->Create(rect.right - rect.left, rect.bottom - rect.top, 32);

	HDC device_context_handle = print->GetDC();
	::PrintWindow(windowHandle, device_context_handle, PW_CLIENTONLY);

	return print;
}

void WindowPrinter::PrintAndSaveToFile(std::string filePath)
{
	auto print = PrintWindow();
	print->Save(filePath.c_str());
	print->ReleaseDC();
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
