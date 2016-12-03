#pragma once
#include "ProcessPipeline.h"
#include <memory>

namespace helmesjo {
	class Image;
	struct ImageMatcher;

	class WindowTask : public ProcessTask {
	public:
		WindowTask(std::shared_ptr<Image> topLeftRefImage, std::shared_ptr<Image> botRightRefImage);
		
		virtual void process(GridData& inout) const override;

	private:
		std::shared_ptr<Image> topLeftRefImage;
		std::shared_ptr<Image> botRightRefImage;
	};
}
