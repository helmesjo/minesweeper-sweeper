#include <catch.hpp>
#include <algorithm>

#include "Sweeper.h"
#include "Grid.h"
#include "Tile.h"

using namespace helmesjo;
using State = Tile::State;

SCENARIO("Solving grid", "[Sweeper]") {
	GIVEN("a 3x3 grid") {
		auto grid = Grid(3, 3, Tile::State::Unknown);
		auto sweeper = Sweeper(grid);

		WHEN("tile (1, 1) is number 1") {
			auto tile = grid.getTile(1, 1);
			grid.setTileState(tile.x, tile.y, State::Number);
			sweeper.calculateMineProbabilities(grid);

			THEN("adjacent tiles should have a mine-probability of 1/8 (1/nrAdjacent)") {
				auto adjacent = grid.getAdjacent(tile);
				const double expectedMineProbability = 1.0 / adjacent.size();

				for (auto tile : adjacent)
				{
					auto mineProbability = sweeper.getMineProbability(tile);
					REQUIRE(mineProbability == expectedMineProbability);
				}
			}
		}
	}

	GIVEN("a 2x1 grid with all unknown") {
		auto grid = Grid(2, 1);

		WHEN("tile (0, 0) is a number with value 1") {
			grid.setTileState(0, 0, State::Number);
			
			THEN("suggest tile (1, 0) is marked with flag (it's a bomb)") {
				//auto nextMove = sweeper.findNextMove(grid);
				//
				//auto suggestedTile = nextMove.tile;
				//auto suggestedColumn = nextMove.tile.x;
				//REQUIRE(suggestedTile.state == State::Flag);
				//REQUIRE(suggestedColumn == 0);
				FAIL();
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