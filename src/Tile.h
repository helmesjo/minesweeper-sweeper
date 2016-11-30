#pragma once

// Don't want this here, but can't get Catch::toString working (if so, it would be defined for tests only)
#include <ostream>

namespace helmesjo {
	struct Tile {
		enum class State : char {
			None	= 0,
			Unknown = 1 << 0,
			Flag	= 1 << 1,
			Number	= 1 << 2,
			All		= -1
		};

		Tile() = default;
		Tile(State state, unsigned int adjacentMines);

		State state = State::Unknown;
		unsigned int adjacentMines = 0u;
		// This is really an external concern (solver), but convinient to store here
		double mineProbability = 0u;
	};

	inline Tile::State operator|(Tile::State a, Tile::State b) {
		return a = static_cast<Tile::State> (static_cast<int>(a) | static_cast<int>(b));
	}

	inline Tile::State operator&(Tile::State a, Tile::State b) {
		return a = static_cast<Tile::State> (static_cast<int>(a) & static_cast<int>(b));
	}

	std::ostream& operator << (std::ostream& os, Tile::State state);
}
