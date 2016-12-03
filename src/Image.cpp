#include "Image.h"
#include "CImg.h"

using namespace helmesjo;

Image::Image(const std::string& filepath) :
	image(std::make_unique<CImg>(filepath.c_str()))
{
}

Image::Image(std::unique_ptr<CImg> img):
	image(std::move(img))
{
}

Image::~Image() = default;

size_t helmesjo::Image::width() const
{
	return image->width();
}

size_t helmesjo::Image::height() const
{
	return image->height();
}

Color helmesjo::Image::getPixel(size_t x, size_t y) const
{
	auto img = *image;
	auto r = img(x, y, 0, 0);
	auto g = img(x, y, 0, 1);
	auto b = img(x, y, 0, 2);

	return Color{ r, g, b };
}

Image helmesjo::Image::getSubImage(size_t fromX, size_t fromY, size_t toX, size_t toY) const
{
	auto crop = image->get_crop(fromX, fromY, toX, toY);
	auto owner = std::unique_ptr<CImg>(new CImg(std::move(crop)));
	return Image(std::move(owner));
}

bool helmesjo::Image::operator==(const Image & other) const
{
	// Different dimensions?
	if (this == &other)
		return true;
	else if (width() != other.width() || height() != other.height())
		return false;

	// Super-naive implementation: Begging for optimization!
	Color color1;
	Color color2;
	cimg_forXY(*image, x, y) {
		color1 = getPixel(x, y);
		color2 = other.getPixel(x, y);

		if(color1 != color2)
			return false;
	}

	return true;
}

bool helmesjo::Image::operator!=(const Image & other) const
{
	return !(*this == other);
}

std::ostream & helmesjo::operator<<(std::ostream & os, Color color)
{
	os << "(" << color.r << "," << color.g << "," << color.b << ")";
	return os;
}
