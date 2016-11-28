#include "Sweeper.h"
#include "Grid.h"
#include <algorithm>
#include <tuple>
#include <stdexcept>

using namespace helmesjo;

static int rowBasedIndex(unsigned int width, unsigned int x, unsigned int y) {
	return width * y + x;
}

helmesjo::Sweeper::Sweeper(const Grid & grid):
	grid(grid),
	mineProbabilities(grid.getWidth() * grid.getHeight(), 0.0)
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
			auto adjacent = grid.getAdjacent(tile);
			if (adjacent.size() > 0) {
				auto mineProbability = static_cast<double>(tile.stateValue) / static_cast<double>(adjacent.size());
				for (auto& adj : adjacent)
					addMineProbability(adj, mineProbability);
			}
		}
	}
}

double helmesjo::Sweeper::getMineProbability(Tile tile) const
{
	auto index = rowBasedIndex(grid.getWidth(), tile.x, tile.y);
	return mineProbabilities[index];
}

void helmesjo::Sweeper::addMineProbability(Tile tile, double probability)
{
	auto index = rowBasedIndex(grid.getWidth(), tile.x, tile.y);
	mineProbabilities[index] += probability;
}

void helmesjo::Sweeper::resetProbabilities()
{
	for (auto prob : mineProbabilities)
		prob = 0.0;
}
