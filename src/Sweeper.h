#pragma once

#include "Tile.h"
#include <vector>
#include "Grid.h"

namespace helmesjo {

	class Sweeper {
	public:
		xy findLeastProbableMine(Grid<Tile>& grid);

		// Clean up below: INTERNAL DETAILS
		void calculateMineProbabilities(Grid<Tile>& grid);
		double getMineProbability(size_t x, size_t y, const Grid<Tile>& grid) const;

	private:
		void resetProbabilities(Grid<Tile>& grid);
	};

}