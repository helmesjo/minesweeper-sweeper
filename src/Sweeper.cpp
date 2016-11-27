#include "Sweeper.h"
#include "Grid.h"

using namespace helmesjo;

GridMove helmesjo::Sweeper::findNextMove(const Grid & grid)
{
	Tile tile{ Tile::State::Flag };
	return GridMove(0, 0, tile);
}
