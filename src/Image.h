#pragma once

#include <string>
#include <memory>

namespace cimg_library {
	template<typename T>
	struct CImg;
}

namespace helmesjo {
	using CImg = cimg_library::CImg<unsigned int>;

	struct Color {
		unsigned int r, g, b;
	};

	class Image {
	public:
		Image(const std::string& filepath);
		~Image();

		Color getPixel(unsigned int x, unsigned int y);

	private:
		std::unique_ptr<CImg> image;
	};

}