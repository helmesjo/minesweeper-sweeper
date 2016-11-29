#include "TileGrid.h"
#include <array>

using namespace helmesjo;

helmesjo::TileGrid::TileGrid(unsigned int nrColumns, unsigned int nrRows, Tile::State defaultState):
	width(nrColumns),
	height(nrRows),
	grid(nrColumns, nrRows)
{
	for (auto x = 0u; x < nrColumns; x++)
		for (auto y = 0u; y < nrRows; y++)
			setTile(Tile(defaultState, 0u, x, y));
}

unsigned int helmesjo::TileGrid::getWidth() const
{
	return width;
}

unsigned int helmesjo::TileGrid::getHeight() const
{
	return height;
}

unsigned int helmesjo::TileGrid::size() const
{
	return grid.size();
}

Tile helmesjo::TileGrid::getTile(unsigned int x, unsigned int y) const
{
	return grid.get(x, y);
}

void helmesjo::TileGrid::setTile(Tile tile)
{
	grid.get(tile.x, tile.y) = tile;
}

std::vector<Tile> helmesjo::TileGrid::getAdjacent(Tile tile, Tile::State included) const
{
	auto adjacent = grid.getAdjacent(tile.x, tile.y);

	auto filtered = std::vector<Tile>();
	for (auto adj : adjacent)
		if ((included & adj.state) == adj.state)
			filtered.push_back(adj);

	return filtered;
}