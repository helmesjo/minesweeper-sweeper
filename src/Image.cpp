#include "Image.h"
#include "CImg.h"
#include "PixelPerfectMatcher.h"
#include <memory>

using namespace helmesjo;
using CImg = cimg_library::CImg<unsigned char>;

struct Image::Impl {
	Impl(const std::string& filepath, std::shared_ptr<ImageMatcher> matcher):
		Impl(CImg(filepath.c_str()), std::move(matcher ? matcher : std::make_shared<PixelPerfectMatcher>()))
	{}

	Impl(CImg&& img, std::shared_ptr<ImageMatcher> matcher) :
		image(std::move(img)),
		matcher(std::move(matcher))
	{}

	CImg image;
	std::shared_ptr<ImageMatcher> matcher;
};

Image::Image(const std::string& filepath, std::shared_ptr<ImageMatcher> matcher) :
	pimpl(std::make_unique<Impl>(filepath, std::move(matcher ? matcher : std::make_shared<PixelPerfectMatcher>())))
{
}

helmesjo::Image::Image(const unsigned char * const buffer, size_t width, size_t height):
	pimpl(std::make_unique<Impl>(CImg(buffer, width, height), nullptr))
{
}

Image::Image(std::unique_ptr<Impl> impl):
	pimpl(std::move(impl))
{
}

Image::~Image() = default;
Image & helmesjo::Image::operator=(Image && other) = default;

bool helmesjo::Image::operator==(const Image & other) const
{
	return pimpl->matcher->isMatch(*this, other);
}

bool helmesjo::Image::operator!=(const Image & other) const
{
	return !(*this == other);
}

size_t helmesjo::Image::width() const
{
	return pimpl->image.width();
}

size_t helmesjo::Image::height() const
{
	return pimpl->image.height();
}

Color helmesjo::Image::getPixel(size_t x, size_t y) const
{
	auto img = pimpl->image;
	auto r = img(x, y, 0, 0);
	auto g = img(x, y, 0, 1);
	auto b = img(x, y, 0, 2);

	return Color{ r, g, b };
}

std::unique_ptr<Image> helmesjo::Image::getSubImage(size_t fromX, size_t fromY, size_t toX, size_t toY) const
{
	auto crop = pimpl->image.get_crop(fromX, fromY, toX, toY);
	auto impl = std::make_unique<Impl>(std::move(crop), pimpl->matcher);
	return std::make_unique<Image>(std::move(impl));
}

void helmesjo::Image::saveToPath(std::string path) const
{
	pimpl->image.save_bmp(path.c_str());
}

void helmesjo::Image::debug_PauseAndPreview() const
{
	cimg_library::CImgDisplay main_disp(pimpl->image, "Image-preview");
	CImg visu(width(), height(), 1, 3, 0);
	visu.draw_image(pimpl->image);

	while (!main_disp.is_closed());
}

std::pair<bool, SubRect> helmesjo::Image::findSubImage(const Image & subImage) const
{
	auto subWidth = subImage.width();
	auto subHeight = subImage.height();

	cimg_forXY(pimpl->image, x, y) {
		auto x2 = x + subWidth - 1u;
		auto y2 = y + subHeight - 1u;

		// RED ALERT: Here we're instantiating new image for each step... DON'T! Just want to check colors within some subrect of image!
		auto subImg2 = getSubImage(x, y, x2, y2);

		if (*subImg2 == subImage)
			return std::make_pair(true, SubRect{ static_cast<size_t>(x), static_cast<size_t>(y), x2, y2 });
	}

	return std::make_pair(false, SubRect());
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
