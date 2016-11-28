#pragma once

#include "Tile.h"
#include <vector>

namespace helmesjo {

	class Grid {
		using TileVec = std::vector<Tile>;
	public:
		Grid(unsigned int nrColumns, unsigned int nrRows, Tile::State defaultState = Tile::State::Unknown);

		unsigned int getWidth() const;
		unsigned int getHeight() const;
		unsigned int size() const;

		Tile getTile(unsigned int x, unsigned int y) const;
		void setTile(Tile tile);

		std::vector<Tile> getAdjacent(Tile tile) const;

		TileVec::const_iterator begin() const;
		TileVec::const_iterator end() const;

	private:
		bool isInRange(int x, int y) const;

		const unsigned int width = 0;
		const unsigned int height = 0;
		// Row-order indexed
		TileVec grid;
	};

}
