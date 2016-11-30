#include <catch.hpp>
#include <algorithm>

#include "Sweeper.h"
#include "Tile.h"
#include "Grid.h"

using namespace helmesjo;
using State = Tile::State;

SCENARIO("Calculating mine-probabilities", "[Sweeper]") {
	using TileGrid = helmesjo::Grid<Tile>;

	// Probabilities
	const auto oneSeventh = 1.0 / 7.0;
	const auto oneEighth = 1.0 / 8.0;
	const auto fourEighths = 4.0 / 8.0;
	const auto oneFifth = 1.0 / 5.0;

	GIVEN("a 3x3 grid") {
		auto grid = TileGrid(3, 3);
		auto sweeper = Sweeper(grid);

		WHEN("tile (1, 1) is a number and got 1 adjacent mine") {
			grid.get(1, 1) = { State::Number, 1u };

			THEN("adjacent tiles should have a mine-probability of 1/8 (1/nrAdjacent)") {
				sweeper.calculateMineProbabilities();
				auto tile00Prob = sweeper.getMineProbability(0, 0);
				auto tile10Prob = sweeper.getMineProbability(1, 0);
				auto tile20Prob = sweeper.getMineProbability(2, 0);
				auto tile01Prob = sweeper.getMineProbability(0, 1);
				auto tile21Prob = sweeper.getMineProbability(2, 1);
				auto tile02Prob = sweeper.getMineProbability(0, 2);
				auto tile12Prob = sweeper.getMineProbability(1, 2);
				auto tile22Prob = sweeper.getMineProbability(2, 2);

				REQUIRE(tile00Prob == oneEighth);
				REQUIRE(tile10Prob == oneEighth);
				REQUIRE(tile20Prob == oneEighth);
				REQUIRE(tile01Prob == oneEighth);
				REQUIRE(tile21Prob == oneEighth);
				REQUIRE(tile02Prob == oneEighth);
				REQUIRE(tile12Prob == oneEighth);
				REQUIRE(tile22Prob == oneEighth);
			}

			AND_WHEN("tile (1,2) is a flag") {
				grid.get(1, 2) = { State::Flag, 0u };

				THEN("adjacent tiles should have a mine-probability of 1/7 (1/nrAdjacent, non-unknown are ignored)") {
					sweeper.calculateMineProbabilities();
					auto tile00Prob = sweeper.getMineProbability(0, 0);
					auto tile10Prob = sweeper.getMineProbability(1, 0);
					auto tile20Prob = sweeper.getMineProbability(2, 0);
					auto tile01Prob = sweeper.getMineProbability(0, 1);
					auto tile21Prob = sweeper.getMineProbability(2, 1);
					auto tile02Prob = sweeper.getMineProbability(0, 2);
					auto tile22Prob = sweeper.getMineProbability(2, 2);

					REQUIRE(tile00Prob == oneSeventh);
					REQUIRE(tile10Prob == oneSeventh);
					REQUIRE(tile20Prob == oneSeventh);
					REQUIRE(tile01Prob == oneSeventh);
					REQUIRE(tile21Prob == oneSeventh);
					REQUIRE(tile02Prob == oneSeventh);
					REQUIRE(tile22Prob == oneSeventh);
				}
			}
		}
		WHEN("tile (1, 1) is a number and got 4 adjacent mine") {
			grid.get(1, 1) = { State::Number, 4 };

			THEN("adjacent tiles should have a mine-probability of 4/7 (4/nrAdjacent, non-unknown are ignored)") {
				sweeper.calculateMineProbabilities();
				auto tile00Prob = sweeper.getMineProbability(0, 0);
				auto tile10Prob = sweeper.getMineProbability(1, 0);
				auto tile20Prob = sweeper.getMineProbability(2, 0);
				auto tile01Prob = sweeper.getMineProbability(0, 1);
				auto tile21Prob = sweeper.getMineProbability(2, 1);
				auto tile02Prob = sweeper.getMineProbability(0, 2);
				auto tile22Prob = sweeper.getMineProbability(2, 2);

				REQUIRE(tile00Prob == fourEighths);
				REQUIRE(tile10Prob == fourEighths);
				REQUIRE(tile20Prob == fourEighths);
				REQUIRE(tile01Prob == fourEighths);
				REQUIRE(tile21Prob == fourEighths);
				REQUIRE(tile02Prob == fourEighths);
				REQUIRE(tile22Prob == fourEighths);
			}
		}
	}

	GIVEN("a 3x3 grid") {
		auto grid = TileGrid(3, 3);
		auto sweeper = Sweeper(grid);

		WHEN("tile (1, 2) and (1,0) are a numbers with 1 adjacent mine each") {
			grid.get(1, 2) = { State::Number, 1 };
			grid.get(1, 0) = { State::Number, 1 };

			THEN("tile (1,1) should have the summed up mine-probability of 1/5 + 1/5") {
				sweeper.calculateMineProbabilities();
				auto mineProbability = sweeper.getMineProbability(1, 1);

				const auto expectedProbability = oneFifth + oneFifth;
				REQUIRE(mineProbability == expectedProbability);
			}
		}
	}
}

SCENARIO("Getting best move", "[Sweeper]") {
	using TileGrid = helmesjo::Grid<Tile>;

	GIVEN("a 2x1 grid with all unknown") {
		auto grid = TileGrid(2, 1);
		auto sweeper = Sweeper(grid);

		WHEN("tile (0, 0) is a number with 1 adjacent mine") {
			grid.get(0, 0) = {State::Number, 1};

			THEN("tile (0, 0) will least probably be a bomb") {
				auto safeTile = sweeper.findLeastProbableMine(grid);
				
				REQUIRE(safeTile.state == State::Number);
			}
		}
	}
	//	/*
	//	WHEN("tile (1, 0) has number 1 and other unkown") {
	//	auto tile = Tile{State::One};
	//	grid.setTile(1, 0, tile);
	//
	//	THEN("suggest tile (0, 0) is marked with flag") {
	//	auto nextMove = sweeper.findNextMove(grid);
	//
	//	auto suggestedTile = nextMove.tile;
	//	auto suggestedColumn = nextMove.column;
	//	REQUIRE(suggestedTile.state == State::Flag);
	//	REQUIRE(suggestedColumn == 1);
	//	}
	//	}
	//	*/
	//}
}


/*

psudo



# WINDOWS SIDE:
	Keep this layer as thin as possible

// Get the raw stuff from WinAPI
auto processName = "Minesweeper"s;
HWND minesweeperHandler = FindWindow(processName.c_str(), NULL);

// Create a driver that will take care of external communication
auto msDriver = WindowDriver(minesweeperHandle);

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