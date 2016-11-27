#pragma once

#include "GridMove.h"

namespace helmesjo {

	class Grid;

	class Sweeper {
	public:
		GridMove findNextMove(const Grid& grid);
	};

}