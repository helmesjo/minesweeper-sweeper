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


SCENARIO("Pipeline & Tasks", "[Pipeline]") {

	GIVEN("WindowTask with topleft & botright ref-images") {
		auto gridTopLeftImg = std::make_shared<Image>(getPath(IMG_MINE_GRID_TOPLEFT));
		auto gridBotRightImg = std::make_shared<Image>(getPath(IMG_MINE_GRID_BOTRIGHT));

		auto windowTask = WindowTask(gridTopLeftImg, gridBotRightImg);
		WHEN("passed GridData with image of the window") {
			GridData data(std::make_unique<Image>(getPath(IMG_MINE_WINDOW)));
			THEN("sub-image of grid should be found") {
				windowTask.process(data);
				
				REQUIRE(data.gridImage != nullptr);
				data.gridImage->saveToPath("griddata_grid.bmp");
			}
		}
	}

	GIVEN("GridTask with tile-size") {
		auto gridTask = GridTask(32u, 32u);

		WHEN("finished processing GridData with 9x9 gridImage") {
			GridData data(nullptr);
			data.gridImage = std::make_unique<Image>(getPath(IMG_MINE_GRID));
			gridTask.process(data);

			THEN("there should be 9 columns and 9 rows") {

				REQUIRE(data.nrColumns == 9);
				REQUIRE(data.nrRows == 9);
			}
		}
	}

	GIVEN("TileTask with ref-images for flag-, bomb-, empty- & number tiles") {
		auto flagTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_FLAG));
		auto bombTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_BOMB));
		auto unknownTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_UNKNOWN));
		auto oneTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_ONE));
		auto twoTile = std::make_shared<Image>(getPath(IMG_MINE_TILE_TWO));
		auto tileTask = TileTask(flagTile, bombTile, unknownTile, { oneTile, twoTile });

		WHEN("finished processing GridData with nrColumns & nrRows specified") {
			GridData data(nullptr);
			data.gridImage = std::make_unique<Image>(getPath(IMG_MINE_GRID));
			data.nrColumns = 9;
			data.nrRows = 9;
			data.tileWidth = 32;
			data.tileHeight = 32;
			tileTask.process(data);

			THEN("a grid should be exctractable") {
				auto grid = data.extractResult();

				REQUIRE(data.tileWidth == 32);
				REQUIRE(data.tileHeight == 32);
				REQUIRE(grid->width() == 9);
				REQUIRE(grid->height() == 9);
			}
		}

	}

	/*

	GIVEN("a pipeline with a single task") {
		auto task1 = std::make_unique<
		auto task2 = Task<Output, Input>();

		task1.setNext(task2);
		//auto pipeline = Pipeline<Output, Input>();
		//pipeline.addTask(task);
		WHEN("a process-request is made") {
			THEN("the task will be varified if runnable and requested to process") {

			}
		}
	}
	*/
}