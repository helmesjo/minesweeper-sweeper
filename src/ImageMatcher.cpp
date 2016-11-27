#include "ImageMatcher.h"
#include "Image.h"

using namespace helmesjo;

helmesjo::ImageMatcher::ImageMatcher(const Image & referenceImage) :
	referenceImage(referenceImage)
{
}

bool ImageMatcher::isMatch(const Image & image)
{
	return false;
}
