#pragma once

#include <vector>
#include <array>

namespace helmesjo {
	
	template<typename T>
	class grid {
	public:

		grid(size_t width, size_t height);

		void set(size_t x, size_t y, T& obj);
		decltype(auto) get(size_t x, size_t y) const;
		decltype(auto) get(size_t x, size_t y);
		std::vector<T> getAdjacent(size_t x, size_t y) const;

		decltype(auto) begin() const;
		decltype(auto) end() const;

	private:

		const size_t width = 0, height = 0;
		std::vector<T> elements;
	};





	struct direction {
		char x;
		char y;
	};
	const std::array<direction, 8> directions = { { { -1,-1 } ,{ -1,0 } ,{ -1,1 } ,{ 0,-1 } ,{ 0,1 } ,{ 1,-1 } ,{ 1,0 } ,{ 1,1 } } };

	static bool isInRange(size_t width, size_t height, int x, int y)
	{
		return x >= 0 && x < static_cast<int>(width) && y >= 0 && y < static_cast<int>(height);
	}

	static int rowBasedIndex(size_t width, size_t x, size_t y)
	{
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
	inline void grid<T>::set(size_t x, size_t y, T & obj)
	{
		auto index = rowBasedIndex(width, x, y);
		elements[index] = obj;
	}
	template<typename T>
	inline decltype(auto) helmesjo::grid<T>::get(size_t x, size_t y) const
	{
		auto index = rowBasedIndex(width, x, y);
		return elements[index];
	}
	template<typename T>
	inline decltype(auto) grid<T>::get(size_t x, size_t y)
	{
		auto index = rowBasedIndex(width, x, y);
		return elements[index];
	}
	template<typename T>
	inline std::vector<T> grid<T>::getAdjacent(size_t x, size_t y) const
	{
		auto adjacent = std::vector<T>();
		for (auto dir : directions) {
			int dx = x + dir.x;
			int dy = y + dir.y;

			if (isInRange(width, height, dx, dy)) {
				auto ajdElement = get(dx, dy);
				//if ((included & ajdElement.state) == ajdElement.state)
				adjacent.push_back(ajdElement);
			}
		}
		return adjacent;
	}
	template<typename T>
	inline decltype(auto) grid<T>::begin() const
	{
		return elements.cbegin();
	}
	template<typename T>
	inline decltype(auto) grid<T>::end() const
	{
		return elements.cend();
	}
}