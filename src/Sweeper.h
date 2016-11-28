#pragma once

#include "Grid.h"
#include <vector>

namespace helmesjo {

	class Grid;

	class Sweeper {
	public:
		Sweeper(const Grid& grid);

		//Tile findMostProbableMine();
		void calculateMineProbabilities();
		double getMineProbability(Tile tile) const;

	private:
		void addMineProbability(Tile tile, double probability);
		void resetProbabilities();

		const Grid& grid;
		std::vector<double> mineProbabilities;
	};

}