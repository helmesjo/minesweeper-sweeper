#include <catch.hpp>
#include <cpplocate/cpplocate.h>

#include "PixelPerfectMatcher.h"
#include "Image.h"
#include "resources.h"

using namespace minesweeper_solver_tests;
using namespace helmesjo;
using namespace resources;

SCENARIO("Image matching", "[imagematcher]") {
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

SCENARIO("Scan for subimage", "[ImageScanner]") {
	auto largeImgPath = getPath(IMG_MINE_WINDOW);
	auto subImgPath = getPath(IMG_MINE_TILE_ONE);
	auto notSubImgPath = getPath(IMG_MINE_TILE_FLAG);

	GIVEN("a sub-image part of a larger image") {
		auto largeImg = Image(largeImgPath);
		auto subImg = Image(subImgPath);

		WHEN("sub-image is scanned for in larger image") {
			auto result = largeImg.findSubImage(subImg);

			THEN("return coordinates of sub-image relative to larger image") {
				auto foundImg = std::get<bool>(result);
				auto subRect = std::get<SubRect>(result);
				REQUIRE(foundImg == true);
				auto expectedSubRect = SubRect{ 186u, 234u, 217u, 265u };
				REQUIRE(subRect == expectedSubRect);
			}
		}
	}

	GIVEN("a sub-image NOT part of a larger image") {
		auto largeImg = Image(largeImgPath);
		auto subImg = Image(notSubImgPath);

		WHEN("sub-image is scanned for in larger image") {
			auto result = largeImg.findSubImage(subImg);

			THEN("return false") {
				auto foundImg = std::get<bool>(result);
				REQUIRE(foundImg == false);
			}
		}
	}
}