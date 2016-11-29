#include "TileGrid.h"

#include <catch.hpp>
#include <algorithm>

using namespace helmesjo;
using State = Tile::State;

SCENARIO("Manipulate grid", "[Grid]") {
	auto grid = TileGrid(3, 3);

	GIVEN("a 3x3 grid with all unknown") {
		auto grid = TileGrid(3, 3);

		WHEN("tile is returned for index (2, 2)") {
			auto tile22 = grid.getTile(2, 2);
			THEN("tile has indexes x & y set to (2, 2) respectively") {
				REQUIRE(tile22.x == 2);
				REQUIRE(tile22.y == 2);
			}
		}

		WHEN("tile with a different state is assigned to position (2,2)") {
			auto tile22 = grid.getTile(2, 2);
			tile22.state = Tile::State::Flag;
			grid.setTile(tile22);

			THEN("the tile returned for position (2,2) has the new state") {
				auto tile2 = grid.getTile(tile22.x, tile22.y);

				REQUIRE(tile2.state == tile22.state);
			}
		}
	}
}

SCENARIO("Access grid", "[Grid]") {
	auto grid = TileGrid(3, 3);

	GIVEN("a 3x3 grid with all unknown") {
		auto grid = TileGrid(3, 3);

		WHEN("adjacent are requested for tile (1,1)") {
			auto tile = grid.getTile(1, 1);
			tile.state = State::Flag;
			grid.setTile(tile);
			auto adjacent = grid.getAdjacent(tile);

			THEN("return all tiles except center") {

				REQUIRE(adjacent.size() == 8);
				for (auto tile : adjacent)
					REQUIRE(tile.state != State::Flag);
			}
		}

		WHEN("adjacent are requested for tile (0,0)") {
			auto tile = grid.getTile(0, 0);
			tile.state = State::Flag;
			grid.setTile(tile);
			auto adjacent = grid.getAdjacent(tile);

			THEN("return all 3 adjacent tiles") {
				REQUIRE(adjacent.size() == 3);
				auto hasAboveAdjacent = std::any_of(adjacent.cbegin(), adjacent.cend(), [](auto t) {
					return t.x == 0u && t.y == 1u;
				});
				REQUIRE(hasAboveAdjacent == true);
			}
		}
	}

	GIVEN("a 3x3 grid with all unknown") {
		WHEN("tile (0, 0) has state Flag") {
			auto tile = grid.getTile(0, 0);
			tile.state = State::Flag;
			grid.setTile(tile);
			AND_WHEN("adjacent with state Flag are requested for tile (1,1)") {
				auto tile = grid.getTile(1, 1);
				auto adjacent = grid.getAdjacent(tile, State::Flag);

				THEN("return only tile (0,0)") {

					REQUIRE(adjacent.size() == 1);
					REQUIRE(adjacent[0].state == State::Flag);
				}
			}
		}
	}
}