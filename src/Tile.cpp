#include "Tile.h"

#include <ostream>
#include <string>

helmesjo::Tile::Tile(State state):
	state(state)
{
}

std::ostream & helmesjo::operator<<(std::ostream & os, const Tile::State state)
{
	{
		using State = Tile::State;

		auto name = std::string("");
		switch (state)
		{
		case State::Empty:
			name = "Empty";
			break;
		case State::Flag:
			name = "Flag";
			break;
		case State::One:
			name = "One";
			break;
		}

		return os << name.c_str();
	}
}
