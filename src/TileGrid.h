#pragma once

#include "Tile.h"
#include "grid.h"

namespace helmesjo {

	class TileGrid {
	public:
		TileGrid(unsigned int nrColumns, unsigned int nrRows, Tile::State defaultState = Tile::State::Unknown);

		unsigned int getWidth() const;
		unsigned int getHeight() const;
		unsigned int size() const;

		Tile getTile(unsigned int x, unsigned int y) const;
		void setTile(Tile tile);

		std::vector<Tile> getAdjacent(Tile tile, Tile::State included = Tile::State::All) const;

		decltype(auto) begin() const;
		decltype(auto) end() const;

	private:

		const unsigned int width = 0;
		const unsigned int height = 0;
		// Row-order indexed
		helmesjo::grid<Tile> grid;
	};


	inline decltype(auto) helmesjo::TileGrid::begin() const
	{
		return grid.begin();
	}
	inline decltype(auto) helmesjo::TileGrid::end() const
	{
		return grid.end();
	}

}
