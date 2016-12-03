#include "Image.h"
#include "CImg.h"
#include "PixelPerfectMatcher.h"
#include <memory>

using namespace helmesjo;

Image::Image(const std::string& filepath, std::shared_ptr<ImageMatcher> matcher) :
	image(std::make_unique<CImg>(filepath.c_str())),
	matcher(std::move(matcher ? matcher : std::make_shared<PixelPerfectMatcher>()))
{
}

Image::Image(std::unique_ptr<CImg> img, std::shared_ptr<ImageMatcher> matcher):
	image(std::move(img)),
	matcher(std::move(matcher))
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
	return Image(std::move(owner), matcher);
}

std::pair<bool, SubRect> helmesjo::Image::findSubImage(const Image & subImage) const
{
	auto subWidth = subImage.width();
	auto subHeight = subImage.height();

	// Here we are instantiating new image for each step... DON'T! Just want to check colors
	cimg_forXY(*image, x, y) {
		auto x2 = x + subWidth - 1u;
		auto y2 = y + subHeight - 1u;
		auto subImg2 = getSubImage(x, y, x2, y2);

		if (subImg2 == subImage)
			return std::make_pair(true, SubRect{ static_cast<size_t>(x), static_cast<size_t>(y), x2, y2 });
	}

	return std::make_pair(false, SubRect());
}

bool helmesjo::Image::operator==(const Image & other) const
{
	return matcher->isMatch(*this, other);
}

bool helmesjo::Image::operator!=(const Image & other) const
{
	return !(*this == other);
}

std::ostream & helmesjo::operator<<(std::ostream & os, const Color& color)
{
	os << "(" << color.r << "," << color.g << "," << color.b << ")";
	return os;
}

std::ostream & helmesjo::operator<<(std::ostream & os, const SubRect & color)
{
	os << "(x1:" << color.x1 << ",y1:" << color.y1 << ",x2:" << color.x2 << ",y2:" << color.y2 << ")";
	return os;
}
