#pragma once

#include "Tile.h"

namespace helmesjo {

	struct TileData {
		TileData(Tile tile);

		Tile tile;
		unsigned int isMineProbability = 0u;
	};

}