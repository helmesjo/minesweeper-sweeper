#pragma once

#include <ostream>

namespace helmesjo {

	struct Tile {
		enum class State : char {
			Flag,
			Empty,
			One,
		};

		Tile(State state);

		const State state;
	};

	std::ostream& operator << (std::ostream& os, const Tile::State state);
}