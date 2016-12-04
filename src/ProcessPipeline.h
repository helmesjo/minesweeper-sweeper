#pragma once

#include <vector>
#include <memory>
#include "Image.h"

/*
 * Note: This class holds too much, but the design was a little back and forth so kept it all here for simplicity.
 *		 The whole "Pipeline" can be extracted and generelized, instead of only supporting "Grid Image processing".
 *		 Pipe- & GridData are structures specifically for "Grid image processing" and should not be here.
*/

namespace helmesjo {
	struct Tile;
	template<typename T>
	class Grid;

	using ImgPtr = std::shared_ptr<Image>;

	/* DATA: This is used as input & output value for each task. It holds data that should be read/written to.
			 If no exception is thrown while processing pipeline, createResult will return a complete object.
	*/

	struct GridData {
		GridData(std::shared_ptr<Image> windowImage);
		~GridData();

		// 1. Supplied on creation
		std::shared_ptr<Image> windowImage = nullptr;
		// 2. Setup by WindowTask
		std::shared_ptr<Image> gridImage = nullptr;
		// 3. Setup by GridTask
		size_t nrColumns = 0u, nrRows = 0u, tileWidth = 0u, tileHeight = 0u;
		bool isGameOver = false;
		// 4. Setup by TileTask
		std::unique_ptr<Grid<Tile>> grid = nullptr;
		// 5. Called by user
		std::unique_ptr<Grid<Tile>> extractResult();
	};

	/* TASK: A task does something specific with the input and may (or may no) modify it. Task are chained in some explicit order to achive final result */

	struct ProcessTask {

		virtual ~ProcessTask();
		virtual void process(GridData& inout) const = 0;

	};

	/* PIPELINE: Consists of a chain of tasks. They will process "PipeData" in order. */

	struct PipeData {
		size_t tileWidth, tileHeight;

		ImgPtr gridTopLeft;
		ImgPtr gridBotRight;
		ImgPtr flagTile;
		ImgPtr bombTile;
		ImgPtr unknownTile;
		ImgPtr gameOver;

		std::vector<ImgPtr> numberTiles; // In order
	};

	class ProcessPipeline {
		using TaskPtr = std::unique_ptr<ProcessTask>;

	public:
		static std::unique_ptr<ProcessPipeline> createDefaultPipeline(const PipeData& imgReferences);
		~ProcessPipeline();

		void addTask(TaskPtr task);
		std::unique_ptr<Grid<Tile>> process(GridData& input) const;

	private:
		std::vector<TaskPtr> tasks;
	};


}