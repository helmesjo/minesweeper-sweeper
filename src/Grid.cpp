#include "Grid.h"
#include <array>

using namespace helmesjo;

struct direction {
	char x;
	char y;
};
const std::array<direction, 8> directions = {{{-1,-1} , {-1,0} , {-1,1} , {0,-1} , {0,1} , {1,-1} , {1,0} , {1,1}}};

static int rowBasedIndex(unsigned int width, unsigned int x, unsigned int y) {
	return width * y + x;
}

helmesjo::Grid::Grid(unsigned int nrColumns, unsigned int nrRows, Tile::State defaultState):
	width(nrColumns),
	height(nrRows),
	grid(nrColumns *nrRows)
{
	for (auto x = 0u; x < nrColumns; x++)
		for (auto y = 0u; y < nrRows; y++)
			setTile(Tile(defaultState, 0u, x, y));
}

unsigned int helmesjo::Grid::getWidth() const
{
	return width;
}

unsigned int helmesjo::Grid::getHeight() const
{
	return height;
}

unsigned int helmesjo::Grid::size() const
{
	return grid.size();
}

Tile helmesjo::Grid::getTile(unsigned int x, unsigned int y) const
{
	auto index = rowBasedIndex(width, x, y);
	return grid[index];
}

void helmesjo::Grid::setTile(Tile tile)
{
	auto index = rowBasedIndex(width, tile.x, tile.y);
	grid[index] = tile;
}

Grid::TileVec helmesjo::Grid::getAdjacent(Tile tile, Tile::State included) const
{
	auto adjacent = std::vector<Tile>();
	for (auto dir : directions) {
		int dx = tile.x + dir.x;
		int dy = tile.y + dir.y;

		if (isInRange(dx, dy)) {
			auto ajdTile = getTile(dx, dy);
			if((included & ajdTile.state) == ajdTile.state)
				adjacent.push_back(ajdTile);
		}
	}
	return adjacent;
}

Grid::TileVec::const_iterator helmesjo::Grid::begin() const
{
	return grid.cbegin();
}

Grid::TileVec::const_iterator helmesjo::Grid::end() const
{
	return grid.cend();
}

bool helmesjo::Grid::isInRange(int x, int y) const {
	return x >= 0 && x < static_cast<int>(width) && y >= 0 && y < static_cast<int>(height);
}
