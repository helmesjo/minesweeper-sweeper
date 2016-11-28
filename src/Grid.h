#pragma once

#include "Tile.h"
#include <vector>

namespace helmesjo {

	class Grid {
	public:
		Grid(unsigned int nrColumns, unsigned int nrRows, Tile::State defaultState = Tile::State::Unknown);

		Tile getTile(unsigned int x, unsigned int y) const;
		void setTileState(unsigned int x, unsigned int y, Tile::State state);

		std::vector<Tile> getAdjacent(unsigned int x, unsigned int y) const;

	private:
		bool isInRange(int x, int y) const;

		const unsigned int width = 0;
		const unsigned int height = 0;
		// Row-order indexed
		std::vector<Tile> grid;
	};

}
