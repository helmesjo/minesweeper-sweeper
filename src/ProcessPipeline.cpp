#include "ProcessPipeline.h"
#include "Grid.h"
#include "Tile.h"
#include "Image.h"
#include <iostream>

using namespace helmesjo;

helmesjo::ProcessPipeline::ProcessPipeline(std::vector<TaskPtr> tasks):
	tasks(std::move(tasks))
{
}

helmesjo::ProcessPipeline::~ProcessPipeline() = default;

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

	return input.createResult();
}

std::unique_ptr<Grid<Tile>> helmesjo::GridData::createResult() const
{
	return std::unique_ptr<Grid<Tile>>();
}
