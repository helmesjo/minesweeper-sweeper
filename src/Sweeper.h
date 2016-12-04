#pragma once

#include "Tile.h"
#include <vector>
#include "Grid.h"

namespace helmesjo {
	struct NextMove {
		enum class State {
			IsBomb,
			IsSafe
		};

		xy tile;
		State state;
	};

	class Sweeper {
		using TileGrid = Grid<Tile>;
	public:

		double calculateAdjacentMineProbability(size_t x, size_t y, const TileGrid& grid) const;

		// Clean up below: INTERNAL DETAILS
		void recalculateMineProbabilities(TileGrid& grid);

		double calculateMineProbability(size_t x, size_t y, const TileGrid& grid) const;
		xy findLeastProbableMine(TileGrid& grid);
		xy findMostProbableMine(TileGrid& grid);
		NextMove getNextMove(TileGrid& grid);

	private:
		void resetProbabilities(TileGrid& grid);

		//Grid<double> mineProbabilities;
	};

}