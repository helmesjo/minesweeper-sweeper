#include <catch.hpp>
#include <cpplocate/cpplocate.h>

#include "PixelPerfectMatcher.h"
#include "Image.h"
#include "resources.h"

using namespace minesweeper_solver_tests;
using namespace helmesjo;

SCENARIO("Image matching", "[imagematcher]") {
	using namespace resources;
	auto referenceImage = Image(getPath(IMG_MINE_TILE_FLAG));
	auto imageMatcher = PixelPerfectMatcher();

	GIVEN("two completely different images") {
		auto imagePath = getPath(IMG_MINE_TILE_BOMB);
		auto image = Image(imagePath);

		WHEN("compared") 
		{
			THEN("it's not a match")
			{
				auto isMatch = imageMatcher.isMatch(referenceImage, image);
				REQUIRE(isMatch == false);
			}
		}
	}

	GIVEN("two identical images") {
		auto imagePath = getPath(IMG_MINE_TILE_FLAG);
		auto image = Image(imagePath);

		WHEN("compared")
		{
			THEN("it's a match")
			{
				auto isMatch = imageMatcher.isMatch(referenceImage, image);
				REQUIRE(isMatch == true);
			}
		}
	}

}