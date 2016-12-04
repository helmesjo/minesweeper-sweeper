#pragma once

#include <string>
#include <memory>

namespace helmesjo {
	struct ImageMatcher;

	struct Color {
		unsigned int r, g, b;

		bool operator==(const Color& c2) {
			return r == c2.r && g == c2.g && b == c2.b;
		}
		bool operator!=(const Color& c2) {
			return !(*this == c2);
		}
	};
	std::ostream& operator << (std::ostream& os, const Color& color);

	struct SubRect {
		size_t x1, y1, x2, y2;

		bool operator==(const SubRect& other) {
			return x1 == other.x1 && y1 == other.y1 && x2 == other.x2 && y2 == other.y2;
		}
		bool operator!=(const SubRect& other) {
			return !(*this == other);
		}
	};
	std::ostream& operator << (std::ostream& os, const SubRect& color);

	class Image {
		struct Impl;
	public:
		Image(const std::string& filepath, std::shared_ptr<ImageMatcher> matcher = nullptr);
		Image(std::unique_ptr<Impl> impl);
		~Image();
		Image(Image&& img) = default;
		Image& operator=(Image&& other);
		bool operator==(const Image& other) const;
		bool operator!=(const Image& other) const;

		size_t width() const;
		size_t height() const;
		Color getPixel(size_t x, size_t y) const;

		std::unique_ptr<Image> getSubImage(size_t fromX, size_t fromY, size_t toX, size_t toY) const;
		std::pair<bool, SubRect> findSubImage(const Image& subImage) const;
		// Used for debugging
		void saveToPath(std::string path) const;

	private:

		std::unique_ptr<Impl> pimpl;
	};

}