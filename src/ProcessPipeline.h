#pragma once

#include <vector>
#include <memory>
#include "Image.h"

namespace helmesjo {
	struct Tile;
	template<typename T>
	class Grid;

	/* DATA: This is used as input & output value for each task. It holds data that can be read/written to.*/

	struct GridData {
		std::unique_ptr<Image> windowImage;
		std::unique_ptr<Image> gridImage;

		size_t width, height;

		std::unique_ptr<Grid<Tile>> createResult() const;
	};

	/* TASK: A task does something specific with the input and may (or may no) modify it. Task are chained in some explicit order to achive final result */

	struct ProcessTask {

		virtual ~ProcessTask() = default;
		virtual void process(GridData& inout) const = 0;

	};

	/* PIPELINE: Consists of a chain of tasks. They will process input-data in order. */

	class ProcessPipeline {
		using TaskPtr = std::unique_ptr<ProcessTask>;

	public:
		ProcessPipeline(std::vector<TaskPtr> tasks);
		~ProcessPipeline();

		std::unique_ptr<Grid<Tile>> process(GridData& input) const;

	private:
		std::vector<TaskPtr> tasks;
	};
}