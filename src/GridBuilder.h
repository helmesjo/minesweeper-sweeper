#pragma once

#include <memory>

namespace helmesjo {
	class Tile;
	template<typename T>
	class Grid;

	struct GridBuilder {

		virtual ~GridBuilder() = default;
		virtual std::unique_ptr<Grid<Tile>> createGrid() = 0;

	};
}