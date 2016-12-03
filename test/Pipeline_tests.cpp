#include <catch.hpp>
#include "ProcessPipeline.h"
#include "WindowTask.h"
#include "Image.h"
#include "resources.h"

using namespace helmesjo;
using namespace minesweeper_solver_tests;
using namespace minesweeper_solver_tests::resources;


SCENARIO("Pipeline & Tasks", "[Pipeline]") {

	GIVEN("a WindowTask with topleft & botright ref-images") {
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