#include <catch.hpp>
#include "ProcessPipeline.h"
#include "WindowTask.h"
#include "GridTask.h"
#include "TileTask.h"
#include "Image.h"
#include "Grid.h"
#include "Tile.h"
#include "resources.h"

using namespace helmesjo;
using namespace minesweeper_solver_tests;
using namespace minesweeper_solver_tests::resources;

const unsigned int tileSize = 16u;

std::unique_ptr<WindowTask> createValidWindowTask() {
	auto gridTopLeftImg = std::make_shared<Image>(getPath(IMG_MINE_GRID_TOPLEFT));
	auto gridBotRightImg = std::make_shared<Image>(getPath(IMG_MINE_GRID_BOTRIGHT));
	return std::make_unique<WindowTask>(gridTopLeftImg, gridBotRightImg);
}

std::unique_ptr<GridTask> createValidGridTask() {
	return std::make_unique<GridTask>();
}

std::unique_ptr<TileTask> createValidTileTask() {
	auto flagTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_FLAG));
	auto bombTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_BOMB));
	auto unknownTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_UNKNOWN));
	auto oneTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_ONE));
	auto twoTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_TWO));
	using ImgPtr = std::shared_ptr<Image>;
	return std::unique_ptr<TileTask>(new TileTask(flagTile, bombTile, unknownTile, { oneTile, twoTile }));
}

SCENARIO("Pipeline & Tasks", "[Pipeline]") {

	GIVEN("WindowTask with topleft & botright ref-images") {
		auto windowTask = createValidWindowTask();

		WHEN("passed GridData with image of the window") {
			GridData data(std::make_unique<Image>(getPath(IMG_MINE_WINDOW)));
			THEN("sub-image of grid should be found") {
				windowTask->process(data);
				
				REQUIRE(data.gridImage != nullptr);
				data.gridImage->saveToPath("griddata_grid.bmp");
			}
		}
	}

	GIVEN("GridTask with tile-size") {
		auto gridTask = createValidGridTask();

		WHEN("finished processing GridData with 9x9 gridImage") {
			GridData data(nullptr);
			data.tileWidth = tileSize;
			data.tileHeight = tileSize;
			data.gridImage = std::make_unique<Image>(getPath(IMG_MINE_GRID));
			gridTask->process(data);

			THEN("there should be 9 columns and 9 rows") {

				REQUIRE(data.nrColumns == 9);
				REQUIRE(data.nrRows == 9);
			}
		}
	}

	GIVEN("TileTask with ref-images for flag-, bomb-, empty- & number tiles") {
		auto tileTask = createValidTileTask();

		WHEN("finished processing GridData with nrColumns & nrRows specified") {
			GridData data(nullptr);
			data.gridImage = std::make_unique<Image>(getPath(IMG_MINE_GRID));
			data.nrColumns = 9;
			data.nrRows = 9;
			data.tileWidth = tileSize;
			data.tileHeight = tileSize;
			tileTask->process(data);

			THEN("a grid should be exctractable") {
				auto grid = data.extractResult();

				REQUIRE(data.tileWidth == tileSize);
				REQUIRE(data.tileHeight == tileSize);
				REQUIRE(grid->width() == 9);
				REQUIRE(grid->height() == 9);
			}
		}
	}

	
	GIVEN("a pipeline with WindowTask, GridTask & TileTask in order") {
		auto windowTask = createValidWindowTask();
		auto gridTask = createValidGridTask();
		auto tileTask = createValidTileTask();

		auto pipeline = ProcessPipeline();
		pipeline.addTask(std::move(windowTask));
		pipeline.addTask(std::move(gridTask));
		pipeline.addTask(std::move(tileTask));
		WHEN("processing GridData with only windowImage") {
			GridData data(std::make_unique<Image>(getPath(IMG_MINE_WINDOW)));
			data.tileWidth = tileSize;
			data.tileHeight = tileSize;
			auto grid = pipeline.process(data);

			THEN("a grid will be extractable") {
				REQUIRE(grid->width() == 9);
				REQUIRE(grid->height() == 9);
			}
		}
	}
	
}