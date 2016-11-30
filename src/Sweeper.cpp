#include "Sweeper.h"
#include <algorithm>
#include <tuple>

using namespace helmesjo;

Tile helmesjo::Sweeper::findLeastProbableMine(Grid<Tile>& grid)
{
	// Should return value here instead
	calculateMineProbabilities(grid);
	
	auto min = std::min_element(grid.begin(), grid.end(), [](auto x, auto y) { return x.mineProbability < y.mineProbability; });

	return *min;
}

// Return pair with least- and most probable mines (xy-indeces)
void helmesjo::Sweeper::calculateMineProbabilities(Grid<Tile>& grid)
{
	// Reset probabilities
	resetProbabilities(grid);

	for (auto i = 0u; i < grid.size(); i++) {
		auto tile = grid.get(i);
		// We only care about Number-tiles
		if (tile.state == Tile::State::Number) {
			// Get all nearby "Unknown" tiles (they might be bombs!)
			auto adjacent = grid.getAdjacent(i, [](auto tile, auto x, auto y) {
				return tile.state == Tile::State::Unknown;
			});
			// Add this tiles (i) mine-probability
			if (adjacent.size()) {
				auto mineProbability = static_cast<double>(tile.adjacentMines) / static_cast<double>(adjacent.size());
				for (auto index : adjacent)
					grid.get(index.x, index.y).mineProbability += mineProbability;
			}
		}
	}
}

double helmesjo::Sweeper::getMineProbability(size_t x, size_t y, const Grid<Tile>& grid) const
{
	return grid.get(x, y).mineProbability;
}

void helmesjo::Sweeper::resetProbabilities(Grid<Tile>& grid)
{
	for (auto& tile : grid)
		tile.mineProbability = 0.0; 
}
