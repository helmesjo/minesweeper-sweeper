#include "TileTask.h"
#include "Image.h"
#include "Grid.h"
#include "Tile.h"

using State = helmesjo::Tile::State;

helmesjo::TileTask::TileTask(Imgptr flagTile, Imgptr bombTile, Imgptr unknownTile, std::vector<Imgptr> numberTiles):
	flagTile(std::move(flagTile)),
	bombTile(std::move(bombTile)),
	unknownTile(std::move(unknownTile)),
	numberTiles(std::move(numberTiles))
{
}

helmesjo::TileTask::~TileTask() = default;

void helmesjo::TileTask::process(GridData & data) const
{
	auto& gridImg = *data.gridImage;

	auto grid = std::make_unique<Grid<Tile>>(data.nrColumns, data.nrRows);

	for (auto y = 0u; y < data.nrRows; y++) {
		for (auto x = 0u; x < data.nrColumns; x++) {
			auto dx = x * data.tileWidth;
			auto dy = y * data.tileHeight;
			auto tileImg = gridImg.getSubImage(dx, dy, dx + data.tileWidth-1, dy + data.tileHeight-1);

			auto tile = Tile(State::Empty, 0u);
			if (tileImg->findSubImage(*unknownTile).first)
				tile.state = State::Unknown;
			else if (tileImg->findSubImage(*flagTile).first)
				tile.state = State::Flag;
			else if(tileImg->findSubImage(*bombTile).first)
				tile.state = State::Bomb;
			else {
				for (auto i = 0u; i < numberTiles.size(); i++)
					if (tileImg->findSubImage(*numberTiles[i]).first) {
						tile.state = State::Number;
						tile.adjacentMines = i + 1;
					}
			}
			grid->set(x, y, tile);
		}
	}
		data.grid = std::move(grid);
}
