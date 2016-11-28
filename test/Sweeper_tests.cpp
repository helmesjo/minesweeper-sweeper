#include <catch.hpp>
#include <algorithm>

#include "Sweeper.h"
#include "Grid.h"
#include "Tile.h"

using namespace helmesjo;
using State = Tile::State;

SCENARIO("Calculating mine-probabilities", "[Sweeper]") {
	GIVEN("a 3x3 grid") {
		auto grid = Grid(3, 3, Tile::State::Unknown);
		auto sweeper = Sweeper(grid);
		// Probabilities
		const auto oneEighth = 1.0 / 8.0;
		const auto fourEighths = 4.0 / 8.0;
		const auto oneFifth = 1.0 / 5.0;

		WHEN("tile (1, 1) is a number") {

			auto tile = grid.getTile(1, 1);
			tile.state = State::Number;

			AND_WHEN("it has 1 adjacent mine") {
				tile.stateValue = 1;
				grid.setTile(tile);
				THEN("adjacent tiles should have a mine-probability of 1/8 (1/nrAdjacent)") {
					sweeper.calculateMineProbabilities();
					auto adjacent = grid.getAdjacent(tile);

					for (auto& tile : adjacent)
					{
						auto mineProbability = sweeper.getMineProbability(tile);
						REQUIRE(mineProbability == oneEighth);
					}
				}
			}

			AND_WHEN("it has 4 adjacent mines") {
				tile.stateValue = 4;
				grid.setTile(tile);
				THEN("adjacent tiles should have a mine-probability of 4/8 (4/nrAdjacent)") {
					sweeper.calculateMineProbabilities();
					auto adjacent = grid.getAdjacent(tile);

					for (auto& tile : adjacent)
					{
						auto mineProbability = sweeper.getMineProbability(tile);
						REQUIRE(mineProbability == fourEighths);
					}
				}
			}
			
			AND_WHEN("tile (1, 0) is a number") {
				tile.stateValue = 1;
				grid.setTile(tile);
				auto tile2 = grid.getTile(1, 0);
				tile2.state = State::Number;
				tile2.stateValue = 1;
				grid.setTile(tile2);

				THEN("mine-probability for overlapping adjacent tiles should be combined") {
					sweeper.calculateMineProbabilities();
					auto adjacent = grid.getAdjacent(tile2);

					auto overlapping00 = grid.getTile(0, 0);
					auto mineProbability00 = sweeper.getMineProbability(overlapping00);

					const double expected = oneEighth + oneFifth;
					REQUIRE(mineProbability00 == expected);
				}
			}
		}
	}
}

SCENARIO("Getting best move", "[Sweeper]") {
	auto grid = Grid(3, 3, Tile::State::Unknown);
	auto sweeper = Sweeper(grid);

	//GIVEN("a 2x1 grid with all unknown") {
	//	auto grid = Grid(2, 1);
	//
	//	WHEN("tile (0, 0) is a number with 1 adjacent mine") {
	//		auto tile = grid.getTile(0, 0);
	//		tile.state = State::Number;
	//		tile.stateValue = 1;
	//		grid.setTile(tile);
	//
	//		THEN("suggest tile (1, 0) is marked with flag (it's a bomb)") {
	//			auto nextMove = sweeper.findNextMove(grid);
	//			//
	//			auto suggestedTile = nextMove.tile;
	//			auto suggestedColumn = nextMove.tile.x;
	//			REQUIRE(suggestedTile.state == State::Flag);
	//			REQUIRE(suggestedColumn == 0);
	//		}
	//	}
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