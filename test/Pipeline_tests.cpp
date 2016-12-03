#include <catch.hpp>
#include "ProcessPipeline.h"
#include "WindowTask.h"
#include "GridTask.h"
#include "Image.h"
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
		auto tileImg = Image(getPath(IMG_MINE_TILE_EMPTY));
		auto gridTask = GridTask(tileImg.width(), tileImg.height());

		WHEN("passed GridData with 9x9 gridImage") {
			GridData data(nullptr);
			data.gridImage = std::make_unique<Image>(getPath(IMG_MINE_GRID));

			THEN("there should be 9 columns and 9 rows") {
				gridTask.process(data);

				REQUIRE(data.nrColumns == 9);
				REQUIRE(data.nrRows == 9);
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