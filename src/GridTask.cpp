#include "GridTask.h"

helmesjo::GridTask::GridTask(size_t tileWidth, size_t tileHeight)
{
}

void helmesjo::GridTask::process(GridData & data) const
{
	auto& gridImg = *data.gridImage;

	//gridImg.pauseAndPreview();

	auto width = gridImg.width();
	auto height = gridImg.height();

	// TODO: Determine size of tile by scanning image (need better ImageMatcher)
	//data.tileWidth = tileWidth;
	//data.tileHeight = tileHeight;

	data.nrColumns = std::lround(static_cast<float>(width) / static_cast<float>(data.tileWidth));
	data.nrRows = std::lround(static_cast<float>(height) / static_cast<float>(data.tileHeight));
}
