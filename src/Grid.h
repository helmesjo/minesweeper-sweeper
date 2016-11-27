#pragma once

#include "Tile.h"
#include <vector>

namespace helmesjo {

	class Grid {
	public:
		Grid(unsigned int nrColumns, unsigned int nrRows);

		Tile getTile(unsigned int column, unsigned int row) const;
		void setTile(unsigned int column, unsigned int row, Tile tile);

		std::vector<Tile> getAdjacent(unsigned int column, unsigned int row) const;

	private:
		const unsigned int width = 0;
		// Row-order indexed
		std::vector<Tile> grid;
	};

}
