#pragma once

#include <ostream>

namespace helmesjo {
	struct Tile {
		enum class State : char {
			Unknown = 0,
			Flag,
			One,
		};

		State state;
	};

	std::ostream& operator << (std::ostream& os, Tile::State state);
}
