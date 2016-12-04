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

// Should've done this prettier, but running out of time...
struct Stats {
	unsigned int gamesWon = 1u;
	unsigned int gamesLost = 1u;

	double getWinPercentage() const { return (static_cast<double>(gamesWon) / static_cast<double>(gamesLost)) * 100; }

};
Stats stats;

auto createPipeline() {
	auto pipeData = PipeData();
	pipeData.gridTopLeft = std::make_shared<Image>(getPath(IMG_MINE_GRID_TOPLEFT));
	pipeData.gridBotRight = std::make_shared<Image>(getPath(IMG_MINE_GRID_BOTRIGHT));
	pipeData.flagTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_FLAG));
	pipeData.bombTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_BOMB));
	pipeData.unknownTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_UNKNOWN));
	pipeData.numberTiles = { std::make_shared<Image>(getPath(IMG_MINE_TILE_ONE)), std::make_shared<Image>(getPath(IMG_MINE_TILE_TWO)) };
	pipeData.gameLost = std::make_shared<Image>(getPath(IMG_MINE_GAMELOST));
	pipeData.gameWon = std::make_shared<Image>(getPath(IMG_MINE_GAMEWON));
	
	return ProcessPipeline::createDefaultPipeline(pipeData);
}

bool minesweeperTest_solve(const std::string& processName) {
	// This value should ideally be found using the image-processor, but need better image-comparator
	const size_t tileSize = 16u;

	// 1. Setup driver (communicator with minesweeper window)
	auto windowDriver = WindowDriver(processName);

	// 2. Create a image processing pipeline (transform raw window-print into grid)
	auto pipeline = createPipeline();
	bool wasOver = false; // urgh
	while (true) {
		// 3. get print
		auto print = windowDriver.printWindow();

		GridData gridData(print);
		gridData.tileWidth = tileSize;
		gridData.tileHeight = tileSize;
		auto grid = pipeline->process(gridData);

		if (gridData.isGameLost) {
			if (!wasOver){
				stats.gamesLost++;
				std::cout << "LOST! Win Rate: " << stats.getWinPercentage() << "%" << std::endl;
			}
			Sleep(1000);
		}
		else if (gridData.isGameWon) {
			if (!wasOver) {
				stats.gamesWon++;
				std::cout << "WON! Win Rate: " << stats.getWinPercentage() << "%" << std::endl;
			}
			Sleep(1000);
		}
		else {

			// Solve for next move
			auto sweeper = Sweeper();
			auto next = sweeper.getNextMove(*grid);

			int halfSize = std::lround(tileSize*0.5);
			// Magic numbers are offset for grid in window (ideally should remember this offset when finding grid inside print (print.getSubImage(...)), but time is of the essence!
			next.tile.x = next.tile.x * tileSize + 11 + halfSize;
			next.tile.y = next.tile.y * tileSize + 64 + halfSize;

			// Perform next move (this should definitly be encapsulated in some Command-design, but just had to get it working asap...
			if (next.state == NextMove::State::IsSafe)
				windowDriver.sendLeftClick(next.tile.x, next.tile.y);
			else
				windowDriver.sendRightClick(next.tile.x, next.tile.y);

			Sleep(500);
		}

		wasOver = gridData.isGameLost || gridData.isGameWon;
	}
}

int main(int argc, char* argv[])
{
	const auto processName = "Minesweeper"s;
	
	// Once we start we play to the finish!
	minesweeperTest_solve(processName);

	return 0;
}


/*

psudo



# WINDOWS SIDE:
Keep this layer as thin as possible

auto processName = "Minesweeper"s;
// Create a "driver" that will take care of external communication
// Any OS-specific logic happens inside the "driver" (print window & send input)
auto driver = WindowDriver(processName);

# SOLVER SIDE: Now all windows-specific stuff is done, and we only use internal data-types (non-windows related "equals" cross-platform)

1. Load reference images (used to pattern-match the window etc. to find the grid and the different tiles)
	gridTopLeft = loadImage(...path);
	gridBotRight = loadImage(...path);
	bombTile = loadImage(...path);
...



2: Setup the "image-processor" pipeline
// Setup a "pipeline", which will create a grid-object from the window-print.
// The pipeline constists of a chain of tasks that all work serially (one tasks output is the next tasks input).
	mineMetaData = (ref-images, tilesize etc)
	pipeline = ProcessPipeline::createDefaultPipeline(mineMetaData);

3: Get print
//	Image is a non-windows object part of the solver-lib
	Image windowPrint = msDriver.getWindowPrint();

4: Process the print and generate a tile-grid
	grid = pipeline.process(inputdata);

4: Solve
// Find what to do with which tile
	solver = AbstractMineSolver(); // Let implementation vary: First one is naive, and later should be "real" mathematical implementation
	nextMove = solver.calculateNextMove(grid); // nextMove constains a tile and command (Click or Flag)

5. Perform move
// Send input to minesweeper window
	button = (nextMove.Type == Click ? mouse1 : mouse2);
	command = gridBuilder.getCoords(nextMove.tile);
	driver.performCommand(command)


6. if_not_done(REPEAT_1).

*/