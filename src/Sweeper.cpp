#include "Sweeper.h"
#include <algorithm>
#include <tuple>
#include <limits>

using namespace helmesjo;

xy helmesjo::Sweeper::findLeastProbableMine(TileGrid& grid)
{
	calculateMineProbabilities(grid);
	
	auto max = std::numeric_limits<size_t>::max();
	xy coords{ max, max };
	double minProbability = std::numeric_limits<double>::max();

	for (auto y = 0u; y < grid.height(); y++) {
		for (auto x = 0u; x < grid.width(); x++) {
			auto tile = grid.get(x, y);
			auto mineProbability = getMineProbability(x, y, grid);
			if (tile.state == Tile::State::Unknown && mineProbability < minProbability) {
				coords = { x, y };
				minProbability = mineProbability;
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
			auto mineProbability = getMineProbability(x, y, grid);
			if (tile.state == Tile::State::Unknown && mineProbability > maxProbability) {
				coords = { x, y };
				maxProbability = mineProbability;
			}
		}
	}

	return coords;
}

NextMove helmesjo::Sweeper::getNextMove(TileGrid & grid)
{
	auto safe = findLeastProbableMine(grid);
	auto unsafe = findMostProbableMine(grid);

	auto safeTileProbability = getMineProbability(safe.x, safe.y, grid);
	auto unsafeTileProbability = getMineProbability(unsafe.x, unsafe.y, grid);

	NextMove next;
	if (safeTileProbability - 0.25 < (1.0 - unsafeTileProbability))
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
			auto nrAdjacentFlags = 0u;
			auto adjacent = grid.getAdjacent(i, [&nrAdjacentFlags](auto tile, auto x, auto y) {
				if (tile.state == Tile::State::Flag)
					nrAdjacentFlags++;

				return tile.state == Tile::State::Unknown;
			});
			// Add this tiles (i) mine-probability
			if (adjacent.size() > 0) {
				// This is how likly it is that a mine is around me
				auto mineProbability = nrAdjacentFlags <= tile.adjacentMines ? static_cast<double>(tile.adjacentMines - nrAdjacentFlags) / static_cast<double>(adjacent.size()) : 0.0;
				//auto mineProbability = static_cast<double>(tile.adjacentMines) / static_cast<double>(adjacent.size());
				
				tile.adjacentMineProbability = mineProbability;
				
				grid.set(i, tile);

				//for (auto index : adjacent)
				//	grid.get(index.x, index.y).adjacentMineProbability += mineProbability;
			}
		}
	}
}

double helmesjo::Sweeper::getMineProbability(size_t x, size_t y, const TileGrid& grid) const
{
	auto tile = grid.get(x, y);

	// Can't be bomb
	if (tile.state != Tile::State::Unknown)
		return 0.0;

	// Look through adjacent Number-tiles and detirmine how probable it is that the specifiec tile is a bomb

	auto mineProbability = 0.0;

	auto adjacent = grid.getAdjacent(x, y, [](auto tile, auto x, auto y) {
		return tile.state == Tile::State::Number;
	});

	for (auto index : adjacent) {
		auto adjProbability = grid.get(index.x, index.y).adjacentMineProbability;
		mineProbability += adjProbability;
	}

	return mineProbability;
}

void helmesjo::Sweeper::resetProbabilities(TileGrid& grid)
{
	for (auto& tile : grid)
		tile.adjacentMineProbability = 0.0; 
}
