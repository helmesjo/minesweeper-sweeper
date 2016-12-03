#include "GridBuilder.h"
#include "ImageMatcher.h"

using namespace helmesjo;

helmesjo::GridBuilder::GridBuilder(std::shared_ptr<Image> emptyTileReferenceImage, std::shared_ptr<ImageMatcher> matcher):
	emptyTileReferenceImage(std::move(emptyTileReferenceImage)),
	matcher(matcher)
{
}

Tile helmesjo::GridBuilder::createTile(const Image & img) const
{
	if (matcher->isMatch(*emptyTileReferenceImage, img))
		return Tile(Tile::State::Unknown, 0);
	else
		throw std::exception("Didn't match any known tile!");
}
