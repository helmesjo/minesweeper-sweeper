#pragma once

#include <vector>
#include <memory>
#include "Image.h"

namespace helmesjo {
	struct Tile;
	template<typename T>
	class Grid;

	/* DATA */

	struct GridData {
		std::unique_ptr<Image> windowImage;
		std::unique_ptr<Image> gridImage;

		size_t width, height;

		std::unique_ptr<Grid<Tile>> createResult() const;
	};

	/* TASK */

	struct ProcessTask {

		virtual ~ProcessTask() = default;
		virtual void process(GridData& inout) const = 0;

	};

	/* PIPELINE */

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