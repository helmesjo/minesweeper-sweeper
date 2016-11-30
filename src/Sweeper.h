#pragma once

#include "Tile.h"
#include <vector>
#include "Grid.h"

namespace helmesjo {

	class TileGrid;

	class Sweeper {
	public:
		Sweeper(Grid<Tile>& grid);

		Tile findLeastProbableMine(Grid<Tile>& grid);
		void calculateMineProbabilities();
		double getMineProbability(size_t x, size_t y) const;

	private:
		void resetProbabilities();

		Grid<Tile>& grid;
	};

}