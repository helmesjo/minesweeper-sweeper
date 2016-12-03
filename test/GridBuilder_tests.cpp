#include <catch.hpp>
#include "Image.h"
#include "resources.h"
#include "GridBuilder.h"
#include "PixelPerfectMatcher.h"

using namespace helmesjo;
using namespace minesweeper_solver_tests::resources;

SCENARIO("Interpret image", "[GridBuilder]") {
	auto gridImg = std::make_shared<Image>(getPath(IMG_MINE_GRID));
	auto emptyTileImg = std::make_shared<Image>(getPath(IMG_MINE_TILE_EMPTY));
	auto matcher = std::make_shared<PixelPerfectMatcher>();

	GIVEN("an image of an empty tile") {
		auto gridBuilder = GridBuilder(emptyTileImg, matcher);
		WHEN("creating grid") {
			THEN("a grid with correct size is created") {
				auto tile = gridBuilder.createTile(*emptyTileImg);

				REQUIRE(tile.state == Tile::State::Unknown);
			}
		}
	}
	GIVEN("an image of an flag tile") {
		auto gridBuilder = GridBuilder(emptyTileImg, matcher);
		WHEN("creating grid") {
			THEN("a grid with correct size is created") {
				auto tile = gridBuilder.createTile(*emptyTileImg);

				REQUIRE(tile.state == Tile::State::Unknown);
			}
		}
	}
}