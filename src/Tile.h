#pragma once

// Don't want this here, but can't get Catch::toString working (if so, it would be defined for tests only)
#include <ostream>

namespace helmesjo {
	struct Tile {
		enum class State : char {
			Unknown = 0,
			Flag,
			Number,
		};

		Tile() = default;
		Tile(State state, unsigned int x, unsigned int y);

		State state = State::Unknown;
		// Ideally, tile shouldn't be aware of it's position, but in this case it simplifies a lot.
		unsigned int x = 0u, y = 0u;
		unsigned int stateValue = 0u;
	};

	std::ostream& operator << (std::ostream& os, Tile::State state);
}
