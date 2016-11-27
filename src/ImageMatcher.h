#pragma once

namespace helmesjo {

	class Image;

	class ImageMatcher {
	public:
		ImageMatcher(const Image& image);

		bool isMatch(const Image& image);

	private:
		const Image& referenceImage;
	};

}