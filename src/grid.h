#pragma once

#include <vector>
#include <array>
#include <tuple>

namespace helmesjo {
	
	template<typename T>
	class grid {
	public:

		grid(size_t width, size_t height);

		size_t width() const;
		size_t height() const;
		size_t size() const;

		void set(size_t x, size_t y, T& obj);
		decltype(auto) get(size_t x, size_t y) const;
		decltype(auto) get(size_t x, size_t y);
		decltype(auto) get(size_t index) const;
		decltype(auto) get(size_t index);
		std::vector<T> getAdjacent(size_t x, size_t y) const;
		std::vector<T> getAdjacent(size_t index) const;

		decltype(auto) begin() const;
		decltype(auto) end() const;

	private:

		const size_t _width = 0, _height = 0;
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

	static size_t calculate1DIndex(size_t width, size_t x, size_t y)
	{
		return width * y + x;
	}

	static auto calculate2DIndex(size_t width, size_t height, size_t index) {
		auto dx = index % width;
		auto dy = index / height;
		return std::make_tuple(dx, dy);
	}

	template<typename T>
	inline helmesjo::grid<T>::grid(size_t width, size_t height) :
		_width(width),
		_height(height),
		elements(width * height, T())
	{
	}

	template<typename T>
	inline size_t grid<T>::width() const
	{
		return _width;
	}

	template<typename T>
	inline size_t grid<T>::height() const
	{
		return _height;
	}

	template<typename T>
	inline size_t grid<T>::size() const
	{
		return elements.size();
	}

	template<typename T>
	inline void grid<T>::set(size_t x, size_t y, T & obj)
	{
		auto index = calculate1DIndex(_width, x, y);
		elements[index] = obj;
	}
	template<typename T>
	inline decltype(auto) grid<T>::get(size_t x, size_t y) const
	{
		auto index = calculate1DIndex(_width, x, y);
		return elements[index];
	}
	template<typename T>
	inline decltype(auto) grid<T>::get(size_t x, size_t y)
	{
		auto index = calculate1DIndex(_width, x, y);
		return elements[index];
	}
	template<typename T>
	inline decltype(auto) grid<T>::get(size_t index) const
	{
		return elements[index];
	}
	template<typename T>
	inline decltype(auto) grid<T>::get(size_t index)
	{
		return elements[index];
	}
	template<typename T>
	inline std::vector<T> grid<T>::getAdjacent(size_t x, size_t y) const
	{
		auto adjacent = std::vector<T>();
		for (auto dir : directions) {
			int dx = x + dir.x;
			int dy = y + dir.y;

			if (isInRange(_width, _height, dx, dy)) {
				auto index = calculate1DIndex(_width, dx, dy);
				auto adjElement = get(index);
				//auto adjElement = get(dy, dx); // This fails, but why this and not above? 
					//	Error: C3779: 'helmesjo::grid<helmesjo::Tile>::get': a function that returns 'decltype(auto)' cannot be used before it is defined
					//	Apparently a bug in MSVC++
				//if ((included & ajdElement.state) == ajdElement.state)
				adjacent.push_back(adjElement);
			}
		}
		return adjacent;
	}
	template<typename T>
	inline std::vector<T> grid<T>::getAdjacent(size_t index) const
	{
		auto xy = calculate2DIndex(_width, _height, index);
		return getAdjacent(std::get<0>(xy), std::get<1>(xy));
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