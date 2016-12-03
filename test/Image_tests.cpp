#include "Image.h"
#include <catch.hpp>
#include "resources.h"

using namespace helmesjo;
using namespace minesweeper_solver_tests;

SCENARIO("Load & Read Image", "[Image]") {
	auto path = resources::getPath(resources::IMG_MINE_TILE_EMPTY);
	auto path2 = resources::getPath(resources::IMG_MINE_TILE_BOMB);

	GIVEN("Some image"){
		Image img(path);
		WHEN("reading pixel-color at (4, 10)") {
			auto color = img.getPixel(4, 10);
			THEN("Pixel-color is correct") {

				REQUIRE(color.r == 192u);
			}
		}
	}

	Image img(path);
	GIVEN("an image of size " + std::to_string(img.width()) + "x" + std::to_string(img.height())) {
		WHEN("a subimage is cropped out from pixel (1,1) to (3,3)") {
			auto subimage = img.getSubImage(1, 1, 3, 3);

			THEN("subimage has size 3x3") {

				REQUIRE(subimage.width() == 3);
				REQUIRE(subimage.height() == 3);
			}
			AND_THEN("corner-colors of subimage are same as from original image") {
				auto color00 = subimage.getPixel(0, 0);
				auto color22 = subimage.getPixel(2, 2);

				REQUIRE(color00 == img.getPixel(1, 1));
				REQUIRE(color22 == img.getPixel(3, 3));
			}
		}
	}

	GIVEN("two equal images (different instances)") {
		Image img1(path);
		Image img2(path);
		WHEN("compared with == operator") {
			auto areEqual = (img1 == img2);
			THEN("they are equal") {
				REQUIRE(areEqual == true);
			}
		}
	}

	GIVEN("two non-equal images (different instances)") {
		Image img1(path);
		Image img2(path2);
		THEN("they are not equal") {
			auto areNotEqual = (img1 != img2);
			REQUIRE(areNotEqual == true);
		}
	}

}