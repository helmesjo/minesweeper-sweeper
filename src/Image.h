#pragma once

#include <string>
#include <memory>

namespace cimg_library {
	template<typename T>
	struct CImg;
}

namespace helmesjo {
	using CImg = cimg_library::CImg<unsigned char>;

	struct Color {
		unsigned int r, g, b;

		bool operator==(const Color& c2) {
			return r == c2.r && g == c2.g && b == c2.b;
		}
		bool operator!=(const Color& c2) {
			return !(*this == c2);
		}
	};
	std::ostream& operator << (std::ostream& os, Color color);

	class Image {
	public:
		Image(const std::string& filepath);
		~Image();
		Image(Image&& img) = default;

		size_t width() const;
		size_t height() const;
		Color getPixel(size_t x, size_t y) const;

		Image getSubImage(size_t fromX, size_t fromY, size_t toX, size_t toY) const;

	private:
		Image(std::unique_ptr<CImg> img);

		std::unique_ptr<CImg> image;
	};

}