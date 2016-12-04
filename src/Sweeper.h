#pragma once

#include "Tile.h"
#include <vector>
#include "Grid.h"

namespace helmesjo {
	using TileGrid = Grid<Tile>;

	struct NextMove {
		enum class State {
			IsBomb,
			IsSafe
		};

		xy tile;
		State state;
	};

	class Sweeper {
	public:

		// Clean up below: INTERNAL DETAILS
		void recalculateMineProbabilities(TileGrid& grid);

		double getMineProbability(size_t x, size_t y, const TileGrid& grid) const;
		xy findLeastProbableMine(TileGrid& grid);
		xy findMostProbableMine(TileGrid& grid);
		NextMove getNextMove(TileGrid& grid);

	private:
		void resetProbabilities(TileGrid& grid);
	};

}