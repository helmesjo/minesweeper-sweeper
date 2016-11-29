#pragma once

#include "Tile.h"
#include <vector>

namespace helmesjo {

	class TileGrid;

	class Sweeper {
	public:
		Sweeper(const TileGrid& grid);

		//Tile findMostProbableMine();
		void calculateMineProbabilities();
		double getMineProbability(Tile tile) const;
		double getMineProbability(unsigned int x, unsigned int y) const;

	private:
		void addMineProbability(Tile tile, double probability);
		void resetProbabilities();

		const TileGrid& grid;
		std::vector<double> mineProbabilities;
	};

}