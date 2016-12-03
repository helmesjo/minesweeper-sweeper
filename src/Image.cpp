#include "Image.h"
#include "CImg.h"

using namespace helmesjo;

Image::Image(const std::string& filepath) :
	image(std::make_unique<CImg>(filepath.c_str()))
{
}

Image::~Image() = default;

Color helmesjo::Image::getPixel(unsigned int x, unsigned int y)
{
	auto img = *image;
	auto r = img(10, 10, 0, 0);
	auto g = img(10, 10, 0, 1);
	auto b = img(10, 10, 0, 2);

	return Color{r, g, b};
}
