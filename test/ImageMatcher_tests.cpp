#include <catch.hpp>
#include <cpplocate/cpplocate.h>

#include "ImageMatcher.h"
#include "Image.h"
#include "resources.h"

using namespace minesweeper_solver_tests;
using namespace helmesjo;

SCENARIO("Image matching", "[imagematcher]") {
	auto referenceImage = Image(resources::IMG_MINE_TILE_FLAG);
	auto imageMatcher = ImageMatcher(referenceImage);

	GIVEN("image matcher contains no/non-matching reference image") {
		auto imagePath = resources::getPath(resources::IMG_MINE_TILE_BOMB);
		auto image = Image(imagePath);

		WHEN("passed image is compared") 
		{
			THEN("it's not a match")
			{
				auto isMatch = imageMatcher.isMatch(image);
				REQUIRE(isMatch == false);
			}
		}
	}

	GIVEN("image matcher contains matching reference image") {
		auto imagePath = resources::getPath(resources::IMG_MINE_TILE_FLAG);
		auto image = Image(imagePath);

		WHEN("passed image is compared")
		{
			THEN("it's a match")
			{
				auto isMatch = imageMatcher.isMatch(image);
				REQUIRE(isMatch == true);
			}
		}
	}

}