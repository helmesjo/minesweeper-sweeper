#pragma once

namespace helmesjo {

	class Image;

	struct ImageMatcher {

		virtual bool isMatch(const Image& lhs, const Image& rhs) const = 0;

	};

}