#pragma once

#include "InputData.h"
#include <windows.h>
#include <string>
#include <memory>

namespace helmesjo {

	class Image;

	class WindowDriver {

	public:
		WindowDriver(const std::string& processName);

		// Whould perferably return a UniquePtr here, but don't want to expose custom deleter-details (to keep it simple in this case). Simplicity vs allocation trade-off...
		std::shared_ptr<Image> printWindow();
		// Debugging only: Remove when done.
		void PrintAndSaveToFile(const std::string& filePath);

		void sendInput(InputData inputObject);

	private:
		HWND windowHandle;
	};
}