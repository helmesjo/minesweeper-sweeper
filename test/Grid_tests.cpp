#include <catch.hpp>
#include <algorithm>

#include "Grid.h"

using namespace helmesjo;
using State = Tile::State;

SCENARIO("Manipulate grid", "[Grid]") {
	auto grid = Grid(3, 3);

	GIVEN("a 3x3 grid with all unknown") {
		auto grid = Grid(3, 3);

		WHEN("tile is returned for index (2, 2)") {
			auto tile22 = grid.getTile(2, 2);
			THEN("tile has indexes x & y set to (2, 2) respectively") {
				REQUIRE(tile22.x == 2);
				REQUIRE(tile22.y == 2);
			}
		}

		WHEN("tile with a different state is assigned to specific position in grid") {
			auto tile22 = grid.getTile(2, 2);
			grid.setTileState(tile22.x, tile22.y, State::Flag);

			THEN("the tile returned for same position has the new state") {
				auto tile2 = grid.getTile(tile22.x, tile22.y);

				REQUIRE(tile2.state != tile22.state);
			}
		}
	}
}

SCENARIO("Access grid", "[Grid]") {
	auto grid = Grid(3, 3);

	GIVEN("a 3x3 grid with all unknown") {
		auto grid = Grid(3, 3);

		WHEN("neighbors are requested for center tile") {
			grid.setTileState(1, 1, State::Flag);
			auto adjacent = grid.getAdjacent(1, 1);

			THEN("return all tiles except center") {

				REQUIRE(adjacent.size() == 8);
				for (auto tile : adjacent)
					REQUIRE(tile.state != State::Flag);
			}
		}

		WHEN("neighbors are requested for corner tile") {
			grid.setTileState(0, 0, State::Flag);
			auto adjacent = grid.getAdjacent(0, 0);

			THEN("return all 3 adjacent tiles") {
				REQUIRE(adjacent.size() == 3);
				auto hasAboveAdjacent = std::any_of(adjacent.cbegin(), adjacent.cend(), [](auto t) {
					return t.x == 0u && t.y == 1u;
				});
				REQUIRE(hasAboveAdjacent == true);
			}
		}
	}
}