#pragma once

#include <vector>
#include <array>

namespace helmesjo {
	
	template<typename T>
	class grid {
	public:

		grid(size_t width, size_t height);

		decltype(auto) get(size_t x, size_t y);

	private:
		const size_t width = 0, height = 0;
		std::vector<T> elements;
	};





	struct direction {
		char x;
		char y;
	};
	const std::array<direction, 8> directions = { { { -1,-1 } ,{ -1,0 } ,{ -1,1 } ,{ 0,-1 } ,{ 0,1 } ,{ 1,-1 } ,{ 1,0 } ,{ 1,1 } } };

	static int rowBasedIndex(unsigned int width, unsigned int x, unsigned int y) {
		return width * y + x;
	}

	template<typename T>
	inline helmesjo::grid<T>::grid(size_t width, size_t height) :
		width(width),
		height(height),
		elements(width * height, T())
	{
	}

	template<typename T>
	inline decltype(auto) helmesjo::grid<T>::get(size_t x, size_t y)
	{
		auto index = rowBasedIndex(width, x, y);
		return elements[index];
	}
}