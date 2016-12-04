#pragma once

#include "ProcessPipeline.h"

namespace helmesjo {
	class GridTask : public ProcessTask {
	public:
		virtual void process(GridData& data) const override;
	};
}
