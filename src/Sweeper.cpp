#include "Sweeper.h"
#include <algorithm>
#include <tuple>
#include <limits>

using namespace helmesjo;

xy helmesjo::Sweeper::findLeastProbableMine(Grid<Tile>& grid)
{
	calculateMineProbabilities(grid);
	
	auto max = std::numeric_limits<size_t>::max();
	xy coords{ max, max };
	double minProbability = std::numeric_limits<double>::max();

	for (auto y = 0u; y < grid.height(); y++) {
		for (auto x = 0u; x < grid.width(); x++) {
			auto tile = grid.get(x, y);
			if (tile.state == Tile::State::Unknown && tile.mineProbability < minProbability) {
				coords = { x, y };
				minProbability = tile.mineProbability;
			}
		}
	}

	return coords;
}


xy helmesjo::Sweeper::findMostProbableMine(TileGrid & grid)
{
	calculateMineProbabilities(grid);

	auto max = std::numeric_limits<size_t>::max();
	xy coords{ max, max };
	double maxProbability = -1000.0;// std::numeric_limits<double>::min();

	for (auto y = 0u; y < grid.height(); y++) {
		for (auto x = 0u; x < grid.width(); x++) {
			auto tile = grid.get(x, y);
			if (tile.state == Tile::State::Unknown && tile.mineProbability > maxProbability) {
				coords = { x, y };
				maxProbability = tile.mineProbability;
			}
		}
	}

	return coords;
}

NextMove helmesjo::Sweeper::getNextMove(TileGrid & grid)
{
	auto safe = findLeastProbableMine(grid);
	auto unsafe = findMostProbableMine(grid);

	auto safeTile = grid.get(safe.x, safe.y);
	auto unsafeTile = grid.get(unsafe.x, unsafe.y);

	NextMove next;
	if (safeTile.mineProbability < (1.0 - unsafeTile.mineProbability))
		next = NextMove{ safe, NextMove::State::IsSafe };
	else
		next = NextMove{ unsafe, NextMove::State::IsBomb };

	return next;
}

// Return pair with least- and most probable mines (xy-indeces)
void helmesjo::Sweeper::calculateMineProbabilities(TileGrid& grid)
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

double helmesjo::Sweeper::getMineProbability(size_t x, size_t y, const TileGrid& grid) const
{
	return grid.get(x, y).mineProbability;
}

void helmesjo::Sweeper::resetProbabilities(TileGrid& grid)
{
	for (auto& tile : grid)
		tile.mineProbability = 0.0; 
}
