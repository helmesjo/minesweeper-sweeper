#include "PixelPerfectMatcher.h"
#include "Image.h"

bool helmesjo::PixelPerfectMatcher::isMatch(const Image & lhs, const Image & rhs) const
{
	// Different dimensions?
	if (lhs.width() != rhs.width() || lhs.height() != rhs.height())
		return false;

	// Super-naive implementation: Begging for optimization!
	Color color1;
	Color color2;

	for (auto x = 0u; x<lhs.width(); x++){
		for(auto y = 0u; y<lhs.height(); y++){
			color1 = lhs.getPixel(x, y);
			color2 = rhs.getPixel(x, y);

			if (color1 != color2)
				return false;
		}
	}

	return true;
}
