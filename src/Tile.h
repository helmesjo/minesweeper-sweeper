#pragma once

// Don't want this here, but can't get Catch::toString working (if so, it would be defined for tests only)
#include <ostream>

namespace helmesjo {
	struct Tile {
		enum class State : char {
			Unknown,
			Flag,
			Number,
		};

		Tile() = default;
		Tile(State state, unsigned int adjacentMines);

		State state = State::Unknown;
		unsigned int adjacentMines = 0u;
		// This is really an external concern (solver), but convenient to store here
		double mineProbability = 0u;
	};

	std::ostream& operator << (std::ostream& os, Tile::State state);
}
