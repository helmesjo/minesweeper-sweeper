#pragma once

#include <memory>
#include "Tile.h"

namespace helmesjo {
	template<typename T>
	class Grid;
	class Image;
	struct ImageMatcher;

	class GridBuilder {
	public:

		GridBuilder(std::shared_ptr<Image> tileReferenceImage, std::shared_ptr<ImageMatcher> matcher);
		Tile createTile(const Image& img) const;

	private:
		std::shared_ptr<Image> emptyTileReferenceImage;
		std::shared_ptr<ImageMatcher> matcher;
	};
}