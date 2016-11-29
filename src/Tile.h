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
		Tile(State state, unsigned int stateValue, unsigned int x, unsigned int y);

		State state = State::Unknown;
		// WILL REMOVE THIS! (was just added as temp convenience)
		unsigned int x = 0u, y = 0u;
		unsigned int stateValue = 0u;
	};

	inline Tile::State operator|(Tile::State a, Tile::State b) {
		return a = static_cast<Tile::State> (static_cast<int>(a) | static_cast<int>(b));
	}

	inline Tile::State operator&(Tile::State a, Tile::State b) {
		return a = static_cast<Tile::State> (static_cast<int>(a) & static_cast<int>(b));
	}

	std::ostream& operator << (std::ostream& os, Tile::State state);
}
