#pragma once

#include "InputData.h"
#include <atlimage.h>
#include <string>
#include <memory>

namespace helmesjo {

	class WindowDriver {

	public:
		WindowDriver(const std::string& processName);

		// Whould perferably return a UniquePtr here, but don't want to expose custom deleter-details (to keep it simple in this case). Simplicity vs Mem trade-off...
		std::shared_ptr<ATL::CImage> printWindow();
		// Debugging only: Remove when done.
		void PrintAndSaveToFile(const std::string& filePath);

		bool sendInput(InputData inputObject);

	private:
		HWND windowHandle;
	};
}