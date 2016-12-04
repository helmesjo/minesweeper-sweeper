#pragma once

#include "ProcessPipeline.h"
#include <memory>

namespace helmesjo {
	class Image;

	class GridTask : public ProcessTask {
	public:
		GridTask(std::shared_ptr<Image> gameLostImg, std::shared_ptr<Image> gameWonImg);

		virtual void process(GridData& data) const override;

	private:
		std::shared_ptr<Image> gameLostImg;
		std::shared_ptr<Image> gameWonImg;
	};
}
