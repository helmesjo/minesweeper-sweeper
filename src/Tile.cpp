#include "Tile.h"
#include "Grid.h"

#include <ostream>
#include <string>
//#include <type_traits>

using namespace helmesjo;

//static_assert(std::is_pod<Tile>::value, "Tile is not POD-type");
static_assert(sizeof(Tile) <= sizeof(int)*4, "Tile needs to be small!");

helmesjo::Tile::Tile(State state, unsigned int stateValue, unsigned int x, unsigned int y) :
	state(state),
	stateValue(stateValue),
	x(x),
	y(y)
{
}

std::ostream & helmesjo::operator<<(std::ostream & os, Tile::State state)
{
	{
		using State = Tile::State;

		auto name = std::string("");
		switch (state)
		{
		case State::Unknown:
			name = "Empty";
			break;
		case State::Flag:
			name = "Flag";
			break;
		case State::Number:
			name = "One";
			break;
		}

		return os << name.c_str();
	}
}