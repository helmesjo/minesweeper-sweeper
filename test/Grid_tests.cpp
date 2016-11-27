#include <catch.hpp>

#include "Grid.h"

using namespace helmesjo;
using State = Tile::State;

SCENARIO("Manipulate grid", "[Grid]") {
	auto grid = Grid(3, 3);

	GIVEN("a 3x3 grid") {
		auto grid = Grid(3, 3);
		auto tile22 = grid.getTile(2, 2);

		WHEN("tile with a different state is assigned to specific position in grid") {
			auto tile = Tile{ State::Flag };
			grid.setTile(1, 1, tile);

			THEN("the tile returned for same position has this new state") {
				auto tile2 = grid.getTile(1, 1);

				REQUIRE(tile2.state != tile22.state);
			}
		}
	}
}

SCENARIO("Access grid", "[Grid]") {
	auto grid = Grid(3, 3);

	GIVEN("a 3x3 grid") {
		auto grid = Grid(3, 3);

		WHEN("neighbors are requested for center tile") {
			auto adjacent = grid.getAdjacent(2, 2);

			THEN("return all 8 adjacent nodes") {

				REQUIRE(adjacent.size() == 8);
			}
		}
	}
}