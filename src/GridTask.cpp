#include "GridTask.h"

helmesjo::GridTask::GridTask(size_t tileWidth, size_t tileHeight):
	tileWidth(tileWidth),
	tileHeight(tileHeight)
{
}

void helmesjo::GridTask::process(GridData & data) const
{
	auto& gridImg = *data.gridImage;

	gridImg.previewAndPause();

	auto width = gridImg.width();
	auto height = gridImg.height();

	// TODO: Determine size of tile by scanning image (need better ImageMatcher)
	data.tileWidth = tileWidth;
	data.tileHeight = tileHeight;

	data.nrColumns = std::lround(static_cast<float>(width) / static_cast<float>(tileWidth));
	data.nrRows = std::lround(static_cast<float>(height) / static_cast<float>(tileHeight));
}
