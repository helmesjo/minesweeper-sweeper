#pragma once

#include "Tile.h"

namespace helmesjo {

	class Grid;

	class Sweeper {
	public:
		Tile findNextMove(const Grid& grid);
	};

}