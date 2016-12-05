#include "Sweeper.h"
#include <algorithm>
#include <tuple>
#include <limits>

using namespace helmesjo;

double helmesjo::Sweeper::calculateAdjacentMineProbability(size_t x, size_t y, const TileGrid & grid) const
{
	auto tile = grid.get(x, y);
	auto adjacentMineProbability = 0.0;

	// Get all nearby "Unknown" tiles (they might be bombs!)
	auto nrAdjacentFlags = 0u;
	auto adjacent = grid.getAdjacent(x, y, [&nrAdjacentFlags](auto tile, auto x, auto y) {
		if (tile.state == Tile::State::Unknown)
			return true;
		else if (tile.state == Tile::State::Flag)
			nrAdjacentFlags++;
		return false;
	});

	// Probability depends on how many adjacent "Unknown" tiles there are (IF flags are correct...)
	if (adjacent.size() > 0 && nrAdjacentFlags <= tile.adjacentMines) {
		// This is how likly it is that a mine is around me
		adjacentMineProbability = nrAdjacentFlags <= tile.adjacentMines ? static_cast<double>(tile.adjacentMines - nrAdjacentFlags) / static_cast<double>(adjacent.size()) : 0.0;
	}

	return adjacentMineProbability;
}

void helmesjo::Sweeper::recalculateMineProbabilities(TileGrid& grid)
{
	// Reset probabilities
	resetProbabilities(grid);

	for (auto y = 0u; y < grid.height(); y++)
		for (auto x = 0u; x < grid.width(); x++)
			grid.get(x, y).adjacentMineProbability = calculateAdjacentMineProbability(x, y, grid);
}

double helmesjo::Sweeper::calculateMineProbability(size_t x, size_t y, const TileGrid& grid) const
{
	auto tile = grid.get(x, y);

	// Can't be bomb
	if (tile.state == Tile::State::Empty || tile.state == Tile::State::Number)
		return 0.0;

	// Look through adjacent Number-tiles and detirmine how probable it is that the specifiec tile is a bomb
	auto adjacent = grid.getAdjacent(x, y, [](auto tile, auto x, auto y) {
		return tile.state == Tile::State::Number;
	});

	// This should be some value calculated from nr of mines on board and unknown tiles
	auto mineProbability = 0.5;

	if (adjacent.size() > 0) {
		for (auto index : adjacent) {
			auto adjProbability = grid.get(index.x, index.y).adjacentMineProbability;
			// Use the lowest probability, since that indicates that this tile has more knowledge from it's neighbors!
			mineProbability = std::max(mineProbability, adjProbability);
		}
	}

	return mineProbability;
}

xy helmesjo::Sweeper::findLeastProbableMine(TileGrid& grid)
{
	recalculateMineProbabilities(grid);
	
	auto max = std::numeric_limits<size_t>::max();
	xy coords{ max, max };
	double minProbability = std::numeric_limits<double>::max();

	for (auto y = 0u; y < grid.height(); y++) {
		for (auto x = 0u; x < grid.width(); x++) {
			auto tile = grid.get(x, y);
			auto mineProbability = calculateMineProbability(x, y, grid);
			if (tile.state == Tile::State::Unknown && mineProbability < minProbability) {
				coords = { x, y };
				minProbability = mineProbability;
			}
		}
	}

	return coords;
}

// GET RID OF THIS COPY PASTE-NONSENSE!
xy helmesjo::Sweeper::findMostProbableMine(TileGrid & grid)
{
	recalculateMineProbabilities(grid);

	auto max = std::numeric_limits<size_t>::max();
	xy coords{ max, max };
	double maxProbability = -1000.0;// std::numeric_limits<double>::min();

	for (auto y = 0u; y < grid.height(); y++) {
		for (auto x = 0u; x < grid.width(); x++) {
			auto tile = grid.get(x, y);
			auto mineProbability = calculateMineProbability(x, y, grid);
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

	auto safeTileProbability = calculateMineProbability(safe.x, safe.y, grid);
	auto unsafeTileProbability = calculateMineProbability(unsafe.x, unsafe.y, grid);

	NextMove next;
	if (unsafeTileProbability < 0.75f)//safeTileProbability*0.95 < (1.0 - unsafeTileProbability))
		next = NextMove{ safe, NextMove::State::IsSafe };
	else
		next = NextMove{ unsafe, NextMove::State::IsBomb };

	return next;
}

void helmesjo::Sweeper::resetProbabilities(TileGrid& grid)
{
	for (auto& tile : grid)
		tile.adjacentMineProbability = 0.5;
}
