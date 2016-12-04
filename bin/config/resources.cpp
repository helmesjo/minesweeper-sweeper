#include "resources.h"
#include <cpplocate\cpplocate.h>

using namespace minesweeper_sweeper;

std::string minesweeper_sweeper::resources::getPath(std::string resourceName)
{
	auto modulePath = cpplocate::getModulePath();
	return modulePath + RESOURCE_FOLDER_PATH + resourceName;
}
