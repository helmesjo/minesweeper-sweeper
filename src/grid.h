#pragma once

#include <vector>
#include <array>
#include <tuple>
#include <functional>

namespace helmesjo {
	struct xy {
		size_t x;
		size_t y;
	};

	// A grid represented in 1D for cache-friendliness (totally not profiled, just a preferred implementation since alot of iterating is happening)
	template<typename T>
	class Grid {
		using Predicate = const std::function<bool(const T&, size_t, size_t)>;
	public:

		Grid(size_t width, size_t height);

		size_t width() const;
		size_t height() const;
		size_t size() const;

		void set(size_t x, size_t y, const T& obj);
		void set(size_t index, const T& obj);
		const T& get(size_t x, size_t y) const;
		T& get(size_t x, size_t y);
		const T& get(size_t index) const;
		T& get(size_t index);
		std::vector<xy> getAdjacent(size_t x, size_t y, Predicate& predicate = nullptr) const;
		std::vector<xy> getAdjacent(size_t index, Predicate& predicate = nullptr) const;

		auto begin();
		auto end();
		auto begin() const;
		auto end() const;

	private:

		const size_t _width = 0, _height = 0;
		std::vector<T> elements;
	};


	struct direction {
		int x;
		int y;
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
	inline helmesjo::Grid<T>::Grid(size_t width, size_t height) :
		_width(width),
		_height(height),
		elements(width * height, T())
	{
	}

	template<typename T>
	inline size_t Grid<T>::width() const
	{
		return _width;
	}

	template<typename T>
	inline size_t Grid<T>::height() const
	{
		return _height;
	}

	template<typename T>
	inline size_t Grid<T>::size() const
	{
		return elements.size();
	}

	template<typename T>
	inline void Grid<T>::set(size_t x, size_t y, const T& obj)
	{
		auto index = calculate1DIndex(_width, x, y);
		elements[index] = obj;
	}
	template<typename T>
	inline void Grid<T>::set(size_t index, const T & obj)
	{
		elements[index] = obj;
	}
	template<typename T>
	inline const T& Grid<T>::get(size_t x, size_t y) const
	{
		auto index = calculate1DIndex(_width, x, y);
		return elements[index];
	}
	template<typename T>
	inline T& Grid<T>::get(size_t x, size_t y)
	{
		auto index = calculate1DIndex(_width, x, y);
		return elements[index];
	}
	template<typename T>
	inline const T& Grid<T>::get(size_t index) const
	{
		return elements[index];
	}
	template<typename T>
	inline T& Grid<T>::get(size_t index)
	{
		return elements[index];
	}
	template<typename T>
	inline std::vector<xy> Grid<T>::getAdjacent(size_t x, size_t y, Predicate& predicate) const
	{
		auto adjacent = std::vector<xy>();

		for (auto dir : directions) {
			int dx = x + dir.x;
			int dy = y + dir.y;

			if (isInRange(_width, _height, dx, dy)) {
				auto& adjElement = get(dx, dy);
				if(predicate == nullptr || predicate(adjElement, dx, dy) == true)
					adjacent.push_back({static_cast<size_t>(dx), static_cast<size_t>(dy)});
			}
		}
		return adjacent;
	}
	template<typename T>
	inline std::vector<xy> Grid<T>::getAdjacent(size_t index, Predicate& predicate) const
	{
		auto xy = calculate2DIndex(_width, _height, index);
		return getAdjacent(std::get<0>(xy), std::get<1>(xy), predicate);
	}
	template<typename T>
	inline auto Grid<T>::begin() const
	{
		return elements.cbegin();
	}
	template<typename T>
	inline auto Grid<T>::end() const
	{
		return elements.cend();
	}
	template<typename T>
	inline auto Grid<T>::begin()
	{
		return elements.begin();
	}
	template<typename T>
	inline auto Grid<T>::end()
	{
		return elements.end();
	}
}