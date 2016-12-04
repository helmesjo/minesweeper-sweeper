#include "GridTask.h"

void helmesjo::GridTask::process(GridData & data) const
{
	auto& gridImg = *data.gridImage;

	auto width = gridImg.width();
	auto height = gridImg.height();

	// TODO: Determine size of tile by scanning image (need better ImageMatcher)
	//data.tileWidth = size...;
	//data.tileHeight = size...;

	data.nrColumns = std::lround(static_cast<float>(width) / static_cast<float>(data.tileWidth));
	data.nrRows = std::lround(static_cast<float>(height) / static_cast<float>(data.tileHeight));
}
