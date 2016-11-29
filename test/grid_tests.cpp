#include "grid.h"

#include <catch.hpp>

using namespace helmesjo;

SCENARIO("Read from grid", "[grid]") {
	using Type = int;

	GIVEN("a 2x2 grid") {
		auto myGrid = grid<Type>(2, 2);

		WHEN("element (1,0) is requested") {
			auto element = myGrid.get(1, 0);

			THEN("a default constructed T is returned") {

				REQUIRE(element == Type());
			}
		}

		WHEN("element (3) is requested") {
			auto element = myGrid.get(3);

			THEN("return elemented (1, 0) (element number three)") {

				REQUIRE(element == Type());
			}
		}
	}

	GIVEN("a 3x3 grid") {
		auto myGrid = grid<Type>(3, 3);

		WHEN("adjacent elements are requested for element (1,1)") {
			auto adjacent = myGrid.getAdjacent(1, 1);

			THEN("all 8 surrounding elements should be returned") {

				REQUIRE(adjacent.size() == 8);
			}
		}

		WHEN("adjacent elements are requested for element (2,2)") {
			auto adjacent = myGrid.getAdjacent(0, 0);

			THEN("3 adjacent elements should be returned") {

				REQUIRE(adjacent.size() == 3);
			}
		}

		WHEN("adjacent elements are requested for element (1,1)") {
			auto adjacent = myGrid.getAdjacent(1, 0);

			THEN("5 adjacent elements should be returned") {

				REQUIRE(adjacent.size() == 5);
			}
		}
	}

	GIVEN("a 3x4 grid") {
		auto myGrid = grid<Type>(3, 4);
		WHEN("size is requested") {
			auto size = myGrid.size();

			THEN("it should be 12") {

				REQUIRE(size == 12);
			}
		}
		WHEN("width is requested") {
			auto width = myGrid.width();

			THEN("it should be 3") {

				REQUIRE(width == 3);
			}
		}
		WHEN("height is requested") {
			auto height = myGrid.height();

			THEN("it should be 4") {

				REQUIRE(height == 4);
			}
		}
	}
}

SCENARIO("Write to grid") {
	GIVEN("a 2x2 grid") {
		using Type = int;
		auto grid = helmesjo::grid<Type>(2, 2);

		WHEN("element (0,1) is assigned a new value") {
			unsigned int x = 0, y = 1;
			Type newVal = 10;
			grid.set(x, y, newVal);

			THEN("it changes the actual element in the grid") {
				auto gridVal01 = grid.get(x, y);

				REQUIRE(gridVal01 == newVal);
			}
		}
	}
}