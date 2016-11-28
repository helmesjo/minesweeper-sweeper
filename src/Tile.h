#pragma once

#include <ostream>

namespace helmesjo {
	struct Tile {
		enum class State : char {
			Unknown = 0,
			Flag,
			One,
		};

		Tile() = default;
		Tile(State state, unsigned int x, unsigned int y);

		State state = State::Unknown;
		unsigned int x = 0u, y = 0u;
		unsigned int mineProbability = 0u;
	};

	std::ostream& operator << (std::ostream& os, Tile::State state);
}
