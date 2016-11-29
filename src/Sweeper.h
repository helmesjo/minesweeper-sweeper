#pragma once

#include "Tile.h"
#include <vector>
#include "Grid.h"

namespace helmesjo {

	class TileGrid;

	class Sweeper {
	public:
		Sweeper(const Grid<Tile>& grid);

		//Tile findMostProbableMine();
		void calculateMineProbabilities();
		double getMineProbability(unsigned int x, unsigned int y) const;

	private:
		void addMineProbability(size_t index, double probability);
		void resetProbabilities();

		const Grid<Tile>& grid;
		helmesjo::Grid<double> mineProbabilities;
	};

}