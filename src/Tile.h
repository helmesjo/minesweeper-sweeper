#pragma once

// Don't want this here, but can't get Catch::toString working (if so, it would be defined for tests only)
#include <ostream>

namespace helmesjo {
	struct Tile {
		enum class State : char {
			Unknown,
			Empty,
			Flag,
			Number,
			Bomb
		};

		Tile() = default;
		Tile(State state, unsigned int adjacentMines);

		State state = State::Unknown;
		unsigned int adjacentMines = 0u;
		// How likely is it that a mine is adjacent to me?
		// This is really an external concern (solver), but convenient to store here
		double adjacentMineProbability = 0u;
	};

	std::ostream& operator << (std::ostream& os, Tile::State state);
}
