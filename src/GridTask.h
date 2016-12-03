#pragma once

#include "ProcessPipeline.h"

namespace helmesjo {
	class GridTask : public ProcessTask {
	public:
		GridTask(size_t tileWidth, size_t tileHeight);

		virtual void process(GridData& data) const override;

	private:
		size_t tileWidth, tileHeight;
	};
}
