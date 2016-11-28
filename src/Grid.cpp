#include "Grid.h"
#include <array>

using namespace helmesjo;

struct direction {
	char x;
	char y;
};
const std::array<direction, 8> directions = {{{-1,-1} , {-1,0} , {-1,1} , {0,-1} , {0,1} , {1,-1} , {1,0} , {1,1}}};

helmesjo::Grid::Grid(unsigned int nrColumns, unsigned int nrRows, Tile::State defaultState):
	width(nrColumns),
	height(nrRows),
	grid(nrColumns *nrRows)
{
	for (auto x = 0u; x < nrColumns; x++)
		for (auto y = 0u; y < nrRows; y++) 
			setTileState(x, y, defaultState);
}

Tile helmesjo::Grid::getTile(unsigned int x, unsigned int y) const
{
	auto index = width * y + x;
	return grid[index];
}

void helmesjo::Grid::setTileState(unsigned int x, unsigned int y, Tile::State state)
{
	auto index = width * y + x;
	grid[index] = Tile(state, x, y);
}

std::vector<Tile> helmesjo::Grid::getAdjacent(unsigned int x, unsigned int y) const
{
	auto adjacent = std::vector<Tile>();
	for (auto dir : directions) {
		int dx = x + dir.x;
		int dy = y + dir.y;

		if (isInRange(dx, dy)) {
			auto tile = getTile(dx, dy);
			adjacent.push_back(tile);
		}
	}
	return adjacent;
}

bool helmesjo::Grid::isInRange(int x, int y) const {
	return x >= 0 && x < static_cast<int>(width) && y >= 0 && y < static_cast<int>(height);
}
