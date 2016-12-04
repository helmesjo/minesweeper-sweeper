#include "GridTask.h"

helmesjo::GridTask::GridTask(std::shared_ptr<Image> gameLostImg, std::shared_ptr<Image> gameWonImg):
	gameLostImg(gameLostImg),
	gameWonImg(gameWonImg)
{
}

void helmesjo::GridTask::process(GridData & data) const
{
	auto& gridImg = *data.gridImage;

	auto width = gridImg.width();
	auto height = gridImg.height();

	// TODO: Determine size of tile by scanning image (need better ImageMatcher. Maybe one that alows skipping alpha, makes refimages less dependant on unrelated details)
	//data.tileWidth = size...;
	//data.tileHeight = size...;

	data.isGameLost = data.windowImage->findSubImage(*gameLostImg).first; // First == if found
	data.isGameWon = data.windowImage->findSubImage(*gameWonImg).first; // First == if found
	data.nrColumns = std::lround(static_cast<float>(width) / static_cast<float>(data.tileWidth));
	data.nrRows = std::lround(static_cast<float>(height) / static_cast<float>(data.tileHeight));
}
