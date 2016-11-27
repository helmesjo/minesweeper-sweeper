#pragma once

#include "Tile.h"

namespace helmesjo {

	struct GridMove {
		GridMove(unsigned int column, unsigned int row, Tile tile);

		const Tile tile;
		const unsigned int column;
		const unsigned int row;
	};

}