#include "Grid.h"

using namespace helmesjo;

struct{
	int dx;
	int dy;
} directions[] = { { -1,-1, },{ -1,0, },{ -1,1 },{ 0,-1 },{ 0,1 },{ 1,-1 },{ 1,0 },{ 1,1 } };

helmesjo::Grid::Grid(unsigned int nrColumns, unsigned int nrRows):
	width(nrColumns)
{
	auto count = nrColumns * nrRows;
	for (auto i = 0u; i < count; i++)
		grid.push_back(Tile());
}

Tile helmesjo::Grid::getTile(unsigned int column, unsigned int row) const
{
	auto index = width * row + column;
	return grid[index];
}

void helmesjo::Grid::setTile(unsigned int column, unsigned int row, Tile tile)
{
	auto index = width * row + column;
	grid[index] = tile;
}

std::vector<Tile> helmesjo::Grid::getAdjacent(unsigned int column, unsigned int row) const
{
	return std::vector<Tile>();
}
