#include "grid.h"

#include <catch.hpp>


SCENARIO("Access elements", "[grid]") {

	GIVEN("a 2x2 grid") {
		using Type = int;
		auto grid = helmesjo::grid<Type>(2, 2);

		WHEN("element (1,0) is requested") {
			grid.get(1, 0) = 10;

			THEN("a default constructed T is returned") {

				//REQUIRE(element == Type());
			}

		}

	}

}