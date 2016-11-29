#pragma once

#include "Tile.h"
#include <vector>
#include "grid.h"

namespace helmesjo {

	class TileGrid;

	class Sweeper {
	public:
		Sweeper(const grid<Tile>& grid);

		//Tile findMostProbableMine();
		void calculateMineProbabilities();
		double getMineProbability(unsigned int x, unsigned int y) const;

	private:
		void addMineProbability(size_t index, double probability);
		void resetProbabilities();

		const grid<Tile>& grid;
		helmesjo::grid<double> mineProbabilities;
	};

}