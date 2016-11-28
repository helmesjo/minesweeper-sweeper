#pragma once

#include "Tile.h"
#include <vector>

namespace helmesjo {

	class Grid;

	class Sweeper {
	public:
		//Tile findNextMove(const Grid& grid);
		void calculateMineProbabilities(const Grid& grid);
		double getMineProbability(Tile tile) const;

	private:
		std::vector<double> mineProbabilities;

	};

}