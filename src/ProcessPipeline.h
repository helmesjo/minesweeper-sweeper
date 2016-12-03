#pragma once

#include <vector>
#include <memory>
#include "Image.h"

namespace helmesjo {
	struct Tile;
	template<typename T>
	class Grid;

	/* DATA: This is used as input & output value for each task. It holds data that can be read/written to.
			 If no exception is thrown while processing pipeline, createResult will return a complete object.
	*/

	struct GridData {
		GridData(std::unique_ptr<Image> windowImage);
		~GridData();

		// 1. Supplied on creation
		std::unique_ptr<Image> windowImage = nullptr;
		// 2. Setup by WindowTask
		std::unique_ptr<Image> gridImage = nullptr;
		// 3. Setup by GridTask
		size_t nrColumns = 0u, nrRows = 0u;
		// 4. Setup by TileTask
		std::unique_ptr<Grid<Tile>> grid = nullptr;
		// 5. Called by user
		std::unique_ptr<Grid<Tile>> extractResult() const;
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