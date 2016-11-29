#include "Sweeper.h"
#include <algorithm>
#include <tuple>
#include <stdexcept>

using namespace helmesjo;

helmesjo::Sweeper::Sweeper(const helmesjo::Grid<Tile> & grid):
	grid(grid),
	mineProbabilities(grid.width(), grid.height())
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

	for (auto i = 0u; i < grid.size(); i++) {
		auto tile = grid.get(i);
		if (tile.state == Tile::State::Number) {
			//auto adjacent = grid.getAdjacent(tile, Tile::State::Unknown);
			auto adjacent = grid.getAdjacent(i);
			auto count = std::count_if(adjacent.begin(), adjacent.end(), [](auto el) { 
				auto val = el.state == Tile::State::Unknown; 
				return val;
			});
			if (count) {
				auto mineProbability = static_cast<double>(tile.adjacentMines) / static_cast<double>(count);
				for (auto i = 0u; i < grid.size(); i++) {
					if (grid.get(i).state == Tile::State::Unknown)
						addMineProbability(i, mineProbability);
				}
			}
		}
	}
}

double helmesjo::Sweeper::getMineProbability(unsigned int x, unsigned int y) const
{
	return mineProbabilities.get(x, y);
}

void helmesjo::Sweeper::addMineProbability(size_t index, double probability)
{
	mineProbabilities.get(index) += probability;
}

void helmesjo::Sweeper::resetProbabilities()
{
	for (auto prob : mineProbabilities)
		prob = 0.0;
}
