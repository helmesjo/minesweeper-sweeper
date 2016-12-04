#include "ProcessPipeline.h"
#include "Grid.h"
#include "Tile.h"
#include "Image.h"
#include "WindowTask.h"
#include "GridTask.h"
#include "TileTask.h"
#include <iostream>

using namespace helmesjo;

helmesjo::ProcessTask::~ProcessTask() = default;

helmesjo::ProcessPipeline::~ProcessPipeline() = default;

void helmesjo::ProcessPipeline::addTask(TaskPtr task)
{
	tasks.push_back(std::move(task));
}

std::unique_ptr<Grid<Tile>> helmesjo::ProcessPipeline::process(GridData & input) const
{
	try
	{
		for (auto& task : tasks)
			task->process(input);
	}
	catch (const std::exception& e)
	{
		std::cout << "Pipeline failed to process data: " << e.what() << std::endl;
		throw e;
	}

	return input.extractResult();
}

helmesjo::GridData::GridData(std::shared_ptr<Image> windowImage) :
	windowImage(std::move(windowImage))
{
}

helmesjo::GridData::~GridData() = default;

std::unique_ptr<Grid<Tile>> helmesjo::GridData::extractResult()
{
	return std::move(grid);
}


std::unique_ptr<WindowTask> createValidWindowTask(ImgPtr gridTopLeftImg, ImgPtr gridBotRightImg) {
	return std::make_unique<WindowTask>(gridTopLeftImg, gridBotRightImg);
}

std::unique_ptr<GridTask> createValidGridTask(size_t tileWith, size_t tileHeight, ImgPtr gameLostImg, ImgPtr gameWonImg) {
	return std::make_unique<GridTask>(gameLostImg, gameWonImg);
}

std::unique_ptr<TileTask> createValidTileTask(ImgPtr flagTile, ImgPtr bombTile, ImgPtr unknownTile, std::vector<ImgPtr> numberTiles) {
	return std::unique_ptr<TileTask>(new TileTask(flagTile, bombTile, unknownTile, numberTiles));
}

std::unique_ptr<ProcessPipeline> ProcessPipeline::createDefaultPipeline(const PipeData& taskData)
{
	auto windowTask = createValidWindowTask(taskData.gridTopLeft, taskData.gridBotRight);
	auto gridTask = createValidGridTask(taskData.tileWidth, taskData.tileHeight, taskData.gameLost, taskData.gameWon);
	auto tileTask = createValidTileTask(taskData.flagTile, taskData.bombTile, taskData.unknownTile, taskData.numberTiles);

	auto pipeline = std::make_unique<ProcessPipeline>();
	pipeline->addTask(std::move(windowTask));
	pipeline->addTask(std::move(gridTask));
	pipeline->addTask(std::move(tileTask));

	return pipeline;
}
