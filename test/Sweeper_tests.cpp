#include <catch.hpp>
#include <algorithm>

#include "Sweeper.h"
#include "Tile.h"
#include "Grid.h"

using namespace helmesjo;
using State = Tile::State;

SCENARIO("Calculating mine-probabilities", "[Sweeper]") {
	using TileGrid = helmesjo::Grid<Tile>;
	auto sweeper = Sweeper();

	// Probabilities
	const auto oneSeventh = 1.0 / 7.0;
	const auto oneEighth = 1.0 / 8.0;
	const auto fourEighths = 4.0 / 8.0;
	const auto oneFifth = 1.0 / 5.0;

	GIVEN("a 3x3 grid") {
		auto grid = TileGrid(3, 3);

		WHEN("tile (1, 1) is a number and got 1 adjacent mine") {
			grid.get(1, 1) = { State::Number, 1u };

			THEN("adjacent tiles should have a mine-probability of 1/8 (1/nrAdjacent)") {
				sweeper.calculateMineProbabilities(grid);
				auto tile00Prob = sweeper.getMineProbability(0, 0, grid);
				auto tile10Prob = sweeper.getMineProbability(1, 0, grid);
				auto tile20Prob = sweeper.getMineProbability(2, 0, grid);
				auto tile01Prob = sweeper.getMineProbability(0, 1, grid);
				auto tile21Prob = sweeper.getMineProbability(2, 1, grid);
				auto tile02Prob = sweeper.getMineProbability(0, 2, grid);
				auto tile12Prob = sweeper.getMineProbability(1, 2, grid);
				auto tile22Prob = sweeper.getMineProbability(2, 2, grid);

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

				THEN("adjacent tiles should have a mine-probability of 0 (1-adjacentFlags/nrAdjacent, non-unknown are ignored)") {
					sweeper.calculateMineProbabilities(grid);
					auto tile00Prob = sweeper.getMineProbability(0, 0, grid);
					auto tile10Prob = sweeper.getMineProbability(1, 0, grid);
					auto tile20Prob = sweeper.getMineProbability(2, 0, grid);
					auto tile01Prob = sweeper.getMineProbability(0, 1, grid);
					auto tile21Prob = sweeper.getMineProbability(2, 1, grid);
					auto tile02Prob = sweeper.getMineProbability(0, 2, grid);
					auto tile22Prob = sweeper.getMineProbability(2, 2, grid);

					REQUIRE(tile00Prob == 0.0);
					REQUIRE(tile10Prob == 0.0);
					REQUIRE(tile20Prob == 0.0);
					REQUIRE(tile01Prob == 0.0);
					REQUIRE(tile21Prob == 0.0);
					REQUIRE(tile02Prob == 0.0);
					REQUIRE(tile22Prob == 0.0);
				}
			}
		}
		WHEN("tile (1, 1) is a number and got 4 adjacent mine") {
			grid.get(1, 1) = { State::Number, 4 };

			THEN("adjacent tiles should have a mine-probability of 4/7 (4/nrAdjacent, non-unknown are ignored)") {
				sweeper.calculateMineProbabilities(grid);
				auto tile00Prob = sweeper.getMineProbability(0, 0, grid);
				auto tile10Prob = sweeper.getMineProbability(1, 0, grid);
				auto tile20Prob = sweeper.getMineProbability(2, 0, grid);
				auto tile01Prob = sweeper.getMineProbability(0, 1, grid);
				auto tile21Prob = sweeper.getMineProbability(2, 1, grid);
				auto tile02Prob = sweeper.getMineProbability(0, 2, grid);
				auto tile22Prob = sweeper.getMineProbability(2, 2, grid);

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

		WHEN("tile (1, 2) and (1,0) are a numbers with 1 adjacent mine each") {
			grid.get(1, 2) = { State::Number, 1 };
			grid.get(1, 0) = { State::Number, 1 };

			THEN("tile (1,1) should have the summed up mine-probability of 1/5 + 1/5") {
				sweeper.calculateMineProbabilities(grid);
				auto mineProbability = sweeper.getMineProbability(1, 1, grid);

				const auto expectedProbability = oneFifth + oneFifth;
				REQUIRE(mineProbability == expectedProbability);
			}
		}
	}
}

SCENARIO("Getting best move", "[Sweeper]") {
	using TileGrid = helmesjo::Grid<Tile>;
	auto sweeper = Sweeper();

	GIVEN("a 3x1 grid with all unknown") {
		auto grid = TileGrid(3, 1);

		WHEN("tile (0, 0) is a number with 1 adjacent mine") {
			grid.get(0, 0) = {State::Number, 1};

			THEN("tile (3, 1) will least probably be a bomb") {
				auto coords = sweeper.findLeastProbableMine(grid);
				auto safeTile = grid.get(coords.x, coords.y);
				
				REQUIRE(safeTile.state == State::Unknown);
				REQUIRE(coords.x == 2);
				REQUIRE(coords.y == 0);
			}
		}
	}
	/*
	GIVEN("a 9x9 grid with all unknown except one") {
		auto grid = TileGrid(9, 9);

		WHEN("tile (1, 2) has probability 0.49 & tile (4, 7) has probability 0.52") {
			auto safeTile = Tile();
			safeTile.state = State::Unknown;
			safeTile.adjacentMineProbability = 0.49;
			grid.set(1, 2, safeTile);

			auto unsafeTile = Tile();
			safeTile.state = State::Unknown;
			safeTile.adjacentMineProbability = 0.52;
			grid.set(4, 7, unsafeTile);

			THEN("then next move should be to click (1,2)") {
				auto nextMove = sweeper.getNextMove(grid);

				REQUIRE(nextMove.state == NextMove::State::IsSafe);
				REQUIRE(nextMove.tile.x == 1);
				REQUIRE(nextMove.tile.y == 2);
			}
		}
	}
	*/
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