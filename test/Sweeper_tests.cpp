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

			const double oneEigthsProbability = 1.0 / 8.0;

			THEN("adjacent tiles should have a mine-probability of 1/8 (1/nrAdjacent)") {
				auto adjacent = grid.getAdjacent(tile);

				for (auto tile : adjacent)
				{
					auto mineProbability = sweeper.getMineProbability(tile);
					REQUIRE(mineProbability == oneEigthsProbability);
				}
			}
			AND_WHEN("tile (1, 0) is number 1") {
				auto tile = grid.getTile(1, 0);
				grid.setTileState(tile.x, tile.y, State::Number);
				sweeper.calculateMineProbabilities(grid);

				const double oneFifthsProbability = 1.0 / 5.0;

				THEN("mine-probability for overlapping tiles should be combined") {
					auto adjacent = grid.getAdjacent(tile);

					auto overlapping00 = grid.getTile(0, 0);
					auto overlapping01 = grid.getTile(0, 1);
					auto overlapping20 = grid.getTile(2, 0);

					auto mineProbability00 = sweeper.getMineProbability(overlapping00);
					auto mineProbability01 = sweeper.getMineProbability(overlapping01);
					auto mineProbability20 = sweeper.getMineProbability(overlapping20);

					const double expected = oneEigthsProbability + oneFifthsProbability;
					REQUIRE(mineProbability00 == expected);
					REQUIRE(mineProbability01 == expected);
					REQUIRE(mineProbability20 == expected);
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