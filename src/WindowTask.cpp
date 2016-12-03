#include "WindowTask.h"

helmesjo::WindowTask::WindowTask(std::shared_ptr<Image> topLeftRefImage, std::shared_ptr<Image> botRightRefImage):
	topLeftRefImage(topLeftRefImage),
	botRightRefImage(botRightRefImage)
{
}

void helmesjo::WindowTask::process(GridData & inout) const
{
	auto& windowImage = inout.windowImage;

	auto topleftResult = windowImage->findSubImage(*topLeftRefImage);
	auto botrightResult = windowImage->findSubImage(*botRightRefImage);

	if (topleftResult.first == false || botrightResult.first == false)
		throw std::exception("WindowTask: Failed to find grid in image");

	auto topLeftRect = topleftResult.second;
	auto botRightRect = botrightResult.second;

	inout.gridImage = windowImage->getSubImage(topLeftRect.x2, topLeftRect.y2, botRightRect.x1, botRightRect.y1);
}
