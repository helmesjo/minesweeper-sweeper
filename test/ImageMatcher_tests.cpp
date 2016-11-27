#include <catch.hpp>
#include <cpplocate/cpplocate.h>

#include "ImageMatcher.h"
#include "Image.h"
#include "resources.h"

using namespace minesweeper_solver_tests;
using namespace helmesjo;

SCENARIO("Image matching", "[imagematcher]") {
	auto imageMatcher = ImageMatcher();

	GIVEN("image matcher contains no/non-matching reference image") {
		auto image = Image(resources::RESOURCE1);

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
		auto image = Image(resources::RESOURCE1);

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