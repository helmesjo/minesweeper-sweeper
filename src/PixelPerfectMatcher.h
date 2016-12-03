#pragma once

#include "ImageMatcher.h"

namespace helmesjo {

	struct PixelPerfectMatcher : public ImageMatcher {

		bool isMatch(const Image& lhs, const Image& rhs) const override;

	};
}
