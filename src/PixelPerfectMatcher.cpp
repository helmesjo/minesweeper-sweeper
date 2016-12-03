#include "PixelPerfectMatcher.h"
#include "Image.h"

bool helmesjo::PixelPerfectMatcher::isMatch(const Image & lhs, const Image & rhs) const
{
	return lhs == rhs;
}
