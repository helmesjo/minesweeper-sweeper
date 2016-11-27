#include "resources.h"
#include <cpplocate\cpplocate.h>

using namespace minesweeper_solver_tests;

std::string minesweeper_solver_tests::resources::getPath(std::string resourceName)
{
	auto modulePath = cpplocate::getModulePath();
	return modulePath + RESOURCE_FOLDER_PATH + resourceName;
}
