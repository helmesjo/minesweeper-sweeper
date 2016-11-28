#include <catch.hpp>
#include <algorithm>

#include "Sweeper.h"
#include "Grid.h"
#include "Tile.h"

using namespace helmesjo;
using State = Tile::State;

SCENARIO("Solving grid", "[Sweeper]") {
	auto sweeper = Sweeper();

	GIVEN("a 3x3 grid with all unknown") {
		auto grid = Grid(3, 3, Tile::State::Unknown);

		WHEN("center tile has number 1") {
			grid.setTileState(0, 0, State::One);

			THEN("associate a mine-probability with adjacent tiles") {
				FAIL();
				//auto hasMineProbabilityGreaterThanZero = std::all_of();
			}
		}
	}

	GIVEN("a 2x1 grid with all unknown") {
		auto grid = Grid(2, 1);

		WHEN("tile (0, 0) has number 1") {
			grid.setTileState(0, 0, State::One);
			
			THEN("suggest tile (0, 0) is marked with flag") {
				auto nextMove = sweeper.findNextMove(grid);

				auto suggestedTile = nextMove.tile;
				auto suggestedColumn = nextMove.tile.x;
				REQUIRE(suggestedTile.state == State::Flag);
				REQUIRE(suggestedColumn == 0);
			}
		}
		/*
		WHEN("tile (1, 0) has number 1 and other unkown") {
			auto tile = Tile{State::One};
			grid.setTile(1, 0, tile);

			THEN("suggest tile (0, 0) is marked with flag") {
				auto nextMove = sweeper.findNextMove(grid);

				auto suggestedTile = nextMove.tile;
				auto suggestedColumn = nextMove.column;
				REQUIRE(suggestedTile.state == State::Flag);
				REQUIRE(suggestedColumn == 1);
			}
		}
		*/
	}
}