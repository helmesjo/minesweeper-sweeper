#include <string>
#include <iostream>
#include <cpplocate/cpplocate.h>
#include "WindowDriver.h"
#include <chrono>
#include <memory>

using namespace helmesjo;
using namespace std;

void sendInputTest() {
	HWND windowHandle = FindWindow("Notepad", NULL);

	//Bring the Notepad window to the front.
	if (!SetForegroundWindow(windowHandle)) {
		cout << "Could not bring window to front: " << endl;
		return;
	}

	unsigned int presses = 5;

	// Create a generic keyboard event structure
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	for (auto i = 0u; i<presses; i++)
	{
		// Press the "Ctrl" key
		ip.ki.wVk = VK_CONTROL;
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));

		// Press the "V" key
		ip.ki.wVk = 'V';
		ip.ki.dwFlags = 0; // 0 for key press
		SendInput(1, &ip, sizeof(INPUT));

		// Release the "V" key
		ip.ki.wVk = 'V';
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));

		// Release the "Ctrl" key
		ip.ki.wVk = VK_CONTROL;
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));

		Sleep(1000); // pause for 1 second
	}
}

void printMinesweeperTest() {
	using std::chrono::high_resolution_clock;
	using std::chrono::milliseconds;

	auto processName = "Minesweeper"s;
	auto windowDriver = WindowDriver(processName);

	auto clock = chrono::high_resolution_clock();
	auto start = clock.now();

	//for (auto i = 0u; i < 1000; i++)
	//	windowPrinter.PrintWindow();

	auto elapsed = std::chrono::duration_cast<milliseconds>(high_resolution_clock::now() - start);
	cout << "Elapsed time: " << elapsed.count() << endl;

	auto filePath = cpplocate::getModulePath() + "/" + "test.jpg";
	windowDriver.PrintAndSaveToFile(filePath);
	//cout << "Printed to file!" << endl;
}

int main(int argc, char* argv[])
{
	//printMinesweeperTest();
	sendInputTest();

	return 0;
}


/*

psudo



# WINDOWS SIDE:
Keep this layer as thin as possible

auto processName = "Minesweeper"s;
// Create a driver that will take care of external communication
// Any OS-specific logic happens inside the "driver"
auto msDriver = WindowDriver(processName);

1: Get print
// Image is a non-windows object declared by the solver
Image windowPrint = msDriver.getWindowPrint();

# SOLVER SIDE: Now all windows-specific stuff is done, and we only use internal data-types (non-windows related = cross-platform)

2: Create grid
// Setup imageMatchers and the grid builder, which will create a grid-object from the window-print
auto gridMatcher = ImageMatcher(gridRefImg);
auto tileMatcher = ImageMatcher(tileRefImg);
auto tileStateMatcher = ImageMatcher(numberOneRefImg, bombRefImg, ...);
auto gridBuilder = GridBuilder(gridMatcher, tileMatcher, tileStateMatcher);

auto grid = gridBuilder.createGrid(windowPrint); // should error-handle here ofcourse

3: Solve
// Find what to do with which tile
auto solver = AbstractMineSolver(); // Let implementation vary: First one is naive, and later should be "real" mathematical implementation
auto safeTile = solver.findLeastProbableMine(grid);
auto unsafeTile = solver.findMostProbableMine(grid);
auto nextMove = solver.decideNextMove(grid); // nextMove constains a tile and command (Click or Flag)

# WINDOWS SIDE:

4. Perform move
// Send input to minesweeper window
auto button = (nextMove.Type == Click ? mouse1 : mouse2);
auto coords = gridBuilder.getCoords(nextMove.tile);
msDriver.sendClick(button, coords.x, coords.y)


5. if_not_done(REPEAT_1).

*/