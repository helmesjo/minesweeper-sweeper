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
		auto tile12 = grid.getTile(1, 2);
		tile12.state = State::Flag;
		grid.setTile(tile12);
		auto sweeper = Sweeper(grid);
		// Probabilities
		const auto oneSeventh = 1.0 / 7.0;
		const auto fourSevenths = 4.0 / 7.0;
		const auto oneFifth = 1.0 / 5.0;

		WHEN("tile (1, 1) is a number and tile (1,2) is a flag") {

			auto tile11 = grid.getTile(1, 1);
			tile11.state = State::Number;

			AND_WHEN("it has 1 adjacent mine") {
				tile11.stateValue = 1;
				grid.setTile(tile11);
				THEN("adjacent tiles should have a mine-probability of 1/7 (1/nrAdjacent, non-unknown are ignored)") {
					sweeper.calculateMineProbabilities();
					auto adjacent = grid.getAdjacent(tile11, State::Unknown);

					for (auto& tile : adjacent)
					{
						auto mineProbability = sweeper.getMineProbability(tile);
						REQUIRE(mineProbability == oneSeventh);
					}
				}
			}

			AND_WHEN("it has 4 adjacent mines") {
				tile11.stateValue = 4;
				grid.setTile(tile11);
				THEN("adjacent tiles should have a mine-probability of 4/7 (4/nrAdjacent, non-unknown are ignored)") {
					sweeper.calculateMineProbabilities();
					auto adjacent = grid.getAdjacent(tile11, State::Unknown);

					for (auto& tile : adjacent)
					{
						auto mineProbability = sweeper.getMineProbability(tile);
						REQUIRE(mineProbability == fourSevenths);
					}
				}
			}
		}
	}

	GIVEN("a 3x3 grid") {
		auto grid = Grid(3, 3, Tile::State::Unknown);
		auto sweeper = Sweeper(grid);
		WHEN("tile (1, 2) and (1,0) are a numbers with 1 adjacent mine each") {
			grid.setTile(Tile(State::Number, 1, 1, 2));
			grid.setTile(Tile(State::Number, 1, 1, 0));
			THEN("tile (1,1) should have the combined mine-probability of 1/5 + 1/5") {
				sweeper.calculateMineProbabilities();
				auto tile11 = grid.getTile(1, 1);
				auto mineProbability = sweeper.getMineProbability(tile11);

				const auto oneFifth = 1.0 / 5.0;
				const auto expectedProbability = oneFifth + oneFifth;
				REQUIRE(mineProbability == expectedProbability);
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