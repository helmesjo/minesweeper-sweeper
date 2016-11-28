#pragma once

#include "Tile.h"

namespace helmesjo {

	struct TileData {
		TileData(Tile tile);

		const Tile tile;
		const unsigned int isMineProbability = 0u;
	};

}