#pragma once

#include "ProcessPipeline.h"
#include <memory>
#include <vector>

namespace helmesjo {
	class Image;
	class TileTask : public ProcessTask {
		using Imgptr = std::shared_ptr<Image>;
	public:
		TileTask(Imgptr flagTile, Imgptr bombTile, Imgptr unknownTile, std::initializer_list<Imgptr> numberTiles);
		~TileTask();

		virtual void process(GridData& data) const override;

	private:
		Imgptr flagTile;
		Imgptr bombTile;
		Imgptr unknownTile;

		std::vector<Imgptr> numberTiles; // in order 1, 2, 3, 4...
	};
}