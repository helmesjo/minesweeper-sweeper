#include <string>
#include <iostream>
#include <cpplocate/cpplocate.h>
#include <chrono>
#include <memory>

#include "resources.h"
#include "WindowDriver.h"
#include "ProcessPipeline.h"
#include "Sweeper.h"
#include "Tile.h"

using namespace helmesjo;
using namespace minesweeper_sweeper::resources;
using namespace std;

void sendInputTest_send_Ctrl_plus_V_to_notepad() {
	HWND windowHandle = FindWindow("Notepad", NULL);

	//Bring the Notepad window to the front.
	if (!SetForegroundWindow(windowHandle)) {
		cout << "Could not bring window to front: " << endl;
		return;
	}

	// Create a generic keyboard event structure
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

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

#define X 123
#define Y 123
#define SCREEN_WIDTH 2048
#define SCREEN_HEIGHT 1152


void MouseSetup(INPUT *buffer)
{
	buffer->type = INPUT_MOUSE;
	buffer->mi.mouseData = 0;
	buffer->mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
	buffer->mi.time = 0;
	buffer->mi.dwExtraInfo = 0;
}

void MouseClick(INPUT *buffer, unsigned int x, unsigned int y)
{
	buffer->mi.dx = (x * (0xFFFF / SCREEN_WIDTH)) + 1;
	buffer->mi.dy = (y * (0xFFFF / SCREEN_HEIGHT)) + 1;

	buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
	SendInput(1, buffer, sizeof(INPUT));

	Sleep(1000);

	buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
	SendInput(1, buffer, sizeof(INPUT));
}

void sendInputTest_send_Mouseclick_at_position() {
	INPUT ip;
	
	MouseSetup(&ip);

	MouseClick(&ip, 400, 400);
}

void minesweeperTest_printWindow(const std::string& processName) {
	using std::chrono::high_resolution_clock;
	using std::chrono::milliseconds;

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

void minesweeperTest_click(const std::string& processName) {
	auto windowDriver = WindowDriver(processName);

	//windowDriver.sendInput({ 128, 128 });

}

void minesweeperTest_solve(const std::string& processName) {
	const size_t tileSize = 16u;

	// Setup driver (communicator with minesweeper window)
	auto windowDriver = WindowDriver(processName);
	// Create a image processing pipeline (transform raw window-print into grid)
	auto pipeData = PipeData();
	pipeData.gridTopLeftImg = std::make_shared<Image>(getPath(IMG_MINE_GRID_TOPLEFT));
	pipeData.gridBotRightImg = std::make_shared<Image>(getPath(IMG_MINE_GRID_BOTRIGHT));
	pipeData.flagTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_FLAG));
	pipeData.bombTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_BOMB));
	pipeData.unknownTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_UNKNOWN));
	pipeData.numberTiles = { std::make_shared<Image>(getPath(IMG_MINE_TILE_ONE)), std::make_shared<Image>(getPath(IMG_MINE_TILE_TWO)) };

	auto pipeline = ProcessPipeline::createDefaultPipeline(pipeData);

	auto print = windowDriver.printWindow();

	GridData gridData(print);
	gridData.tileWidth = tileSize;
	gridData.tileHeight = tileSize;
	auto grid = pipeline->process(gridData);

	auto sweeper = Sweeper();

	auto next = sweeper.getNextMove(*grid);

	int halfSize = tileSize*0.5;

	next.tile.x = next.tile.x * tileSize + 11 + halfSize;
	next.tile.y = next.tile.y * tileSize + 64 + halfSize;
	
	//InputData input = {leastProbableMine.x * tileSize + 11 + halfSize, leastProbableMine.y * tileSize + 64  + halfSize }; // Magic numbers are offset for grid in window

	if(next.state == NextMove::State::IsSafe)
		windowDriver.sendLeftClick(next.tile.x, next.tile.y);
	else
		windowDriver.sendRightClick(next.tile.x, next.tile.y);

}

int main(int argc, char* argv[])
{
	const auto processName = "Minesweeper"s;
	//for (auto i = 0u; i<5; i++)
		//printMinesweeperTest();
	while (true) {
		minesweeperTest_solve(processName);
		Sleep(2000);
	}
	//minesweeperTest_click(processName);
	//sendInputTest_send_Ctrl_plus_V_to_notepad();
	//sendInputTest_send_Mouseclick_at_position();

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

# SOLVER SIDE: Now all windows-specific stuff is done, and we only use internal data-types (non-windows related "equals" cross-platform)

1: Get print
// Image is a non-windows object declared by the solver
Image windowPrint = msDriver.getWindowPrint();

2: Create grid
// Setup imageMatchers and the grid builder, which will create a grid-object from the window-print
auto gridMatcher = ImageMatcher(gridRefImg); (ImageMatcher is abstract, so instances used here are some concrete implementations of that)
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

# WINDOWS SIDE (invoked by solver):

4. Perform move
// Send input to minesweeper window
auto button = (nextMove.Type == Click ? mouse1 : mouse2);
auto coords = gridBuilder.getCoords(nextMove.tile);
msDriver.sendClick(button, coords.x, coords.y)


5. if_not_done(REPEAT_1).

*/