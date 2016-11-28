#include "Sweeper.h"
#include "Grid.h"

using namespace helmesjo;

static int rowBasedIndex(unsigned int width, unsigned int x, unsigned int y) {
	return width * y + x;
}

helmesjo::Sweeper::Sweeper(const Grid & grid):
	grid(grid),
	mineProbabilities(grid.getWidth() * grid.getHeight(), 0.0)
{
}

void helmesjo::Sweeper::calculateMineProbabilities(const Grid & grid)
{
	for (auto tile : grid) {
		if (tile.state == Tile::State::Number) {
			auto adjacent = grid.getAdjacent(tile);
			if (adjacent.size() > 0) {
				// 1.0 should be the number of the tile (or some actual mathematical calculation of probability!)
				auto mineProbability = 1.0 / adjacent.size();
				for (auto adj : adjacent)
					setMineProbability(adj, mineProbability);
			}
		}
	}
}

double helmesjo::Sweeper::getMineProbability(Tile tile) const
{
	auto index = rowBasedIndex(grid.getWidth(), tile.x, tile.y);
	return mineProbabilities[index];
}

void helmesjo::Sweeper::setMineProbability(Tile tile, double probability)
{
	auto index = rowBasedIndex(grid.getWidth(), tile.x, tile.y);
	mineProbabilities[index] = probability;
}
