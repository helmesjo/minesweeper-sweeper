#include <catch.hpp>

#include "Sweeper.h"
#include "Grid.h"
#include "Tile.h"

using namespace helmesjo;

SCENARIO("Find next move", "[Sweeper]") {
	auto sweeper = Sweeper();
	GIVEN("a 2x1 grid") {
		auto grid = Grid(2, 1);
		WHEN("tile (0, 1) has number 1") {
			auto tile01 = Tile(Tile::State::One);
			THEN("suggest tile (0, 0) is marked with flag") {
				auto suggestedTile = sweeper.findNextMove(grid);

				REQUIRE(suggestedTile.state == Tile::State::Flag);
			}
		}
	}
}