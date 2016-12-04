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

using State = Tile::State;

const unsigned int tileSize = 16u;

std::unique_ptr<WindowTask> createValidWindowTask() {
	auto gridTopLeftImg = std::make_shared<Image>(getPath(IMG_MINE_GRID_TOPLEFT));
	auto gridBotRightImg = std::make_shared<Image>(getPath(IMG_MINE_GRID_BOTRIGHT));
	return std::make_unique<WindowTask>(gridTopLeftImg, gridBotRightImg);
}

std::unique_ptr<GridTask> createValidGridTask() {
	auto gameOverImg = std::make_shared<Image>(getPath(IMG_MINE_GAMEOVER));
	return std::make_unique<GridTask>(gameOverImg);
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
			GridData data(std::make_shared<Image>(getPath(IMG_MINE_WINDOW)));
			data.tileWidth = tileSize;
			data.tileHeight = tileSize;
			data.gridImage = std::make_unique<Image>(getPath(IMG_MINE_GRID));
			gridTask->process(data);

			THEN("there should be 9 columns and 9 rows") {

				REQUIRE(data.isGameOver == true);
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

				auto tile52 = grid->get(5, 2);
				auto tile60 = grid->get(6, 0);
				auto tile61 = grid->get(6, 1);
				auto tile63 = grid->get(6, 3);
				auto tile33 = grid->get(3, 3);
				auto tile08 = grid->get(0, 8);

				REQUIRE(data.tileWidth == tileSize);
				REQUIRE(data.tileHeight == tileSize);
				REQUIRE(grid->width() == 9);
				REQUIRE(grid->height() == 9);
				REQUIRE(tile52.state == State::Empty);
				REQUIRE(tile60.state == State::Bomb);
				REQUIRE(tile61.state == State::Number);
				REQUIRE(tile61.adjacentMines == 2);
				REQUIRE(tile63.state == State::Number);
				REQUIRE(tile63.adjacentMines == 1);
				REQUIRE(tile33.state == State::Unknown);
				REQUIRE(tile08.state == State::Flag);
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