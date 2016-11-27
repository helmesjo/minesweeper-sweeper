#include "Tile.h"
#include "Grid.h"

#include <ostream>
#include <string>
#include <type_traits>

static_assert(std::is_pod<helmesjo::Tile>::value, "Tile must be POD-type");

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
		case State::One:
			name = "One";
			break;
		}

		return os << name.c_str();
	}
}
