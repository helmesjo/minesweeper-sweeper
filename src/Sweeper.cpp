#include "Sweeper.h"
#include "TileGrid.h"
#include <algorithm>
#include <tuple>
#include <stdexcept>

using namespace helmesjo;

helmesjo::Sweeper::Sweeper(const TileGrid & grid):
	grid(grid),
	mineProbabilities(grid.getWidth(), grid.getHeight())
{
	if (grid.size() == 0)
		throw std::exception("Can't work with an empty grid");
}

//Tile helmesjo::Sweeper::findMostProbableMine()
//{
//	calculateMineProbabilities();
//	
//	auto min = std::min_element(mineProbabilities.cbegin(), mineProbabilities.cend());
//	
//
//
//	return ;
//}

void helmesjo::Sweeper::calculateMineProbabilities()
{
	resetProbabilities();

	for (auto& tile : grid) {
		if (tile.state == Tile::State::Number) {
			auto adjacent = grid.getAdjacent(tile, Tile::State::Unknown);
			if (adjacent.size() > 0) {
				auto mineProbability = static_cast<double>(tile.adjacentMines) / static_cast<double>(adjacent.size());
				for (auto& adj : adjacent)
					addMineProbability(adj, mineProbability);
			}
		}
	}
}

double helmesjo::Sweeper::getMineProbability(Tile tile) const
{
	return getMineProbability(tile.x, tile.y);
}

double helmesjo::Sweeper::getMineProbability(unsigned int x, unsigned int y) const
{
	auto index = rowBasedIndex(grid.getWidth(), x, y);
	return mineProbabilities.get(x, y);
}

void helmesjo::Sweeper::addMineProbability(Tile tile, double probability)
{
	auto index = rowBasedIndex(grid.getWidth(), tile.x, tile.y);
	mineProbabilities.get(tile.x, tile.y) += probability;
}

void helmesjo::Sweeper::resetProbabilities()
{
	for (auto prob : mineProbabilities)
		prob = 0.0;
}
