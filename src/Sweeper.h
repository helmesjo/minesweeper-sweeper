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
		xy findLeastProbableMine(TileGrid& grid);
		xy findMostProbableMine(TileGrid& grid);
		NextMove getNextMove(TileGrid& grid);

		// Clean up below: INTERNAL DETAILS
		void calculateMineProbabilities(TileGrid& grid);
		double getMineProbability(size_t x, size_t y, const TileGrid& grid) const;

	private:
		void resetProbabilities(TileGrid& grid);
	};

}