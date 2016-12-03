#include <catch.hpp>
#include "Image.h"
#include "resources.h"

using namespace helmesjo;
using namespace minesweeper_solver_tests;

SCENARIO("Load & Read Image", "[Image]") {

	GIVEN("Some image"){
		auto path = resources::getPath(resources::IMG_MINE_TILE_EMPTY);
		Image img(path);
		WHEN("Pixel at (10, 10) is read") {
			auto color = img.getPixel(10, 10);
			THEN("Pixel-color is correct") {

				REQUIRE(color.r == 256u);
			}
		}
	}

}