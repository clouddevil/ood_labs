#pragma once
#include <gsl\gsl_util>

template <typename T>
struct PointT
{
	T x = 0;
	T y = 0;

	PointT() = default;

	template <typename V>
	PointT(V l, V t)
		: x(gsl::narrow_cast<T>(l))
		, y(gsl::narrow_cast<T>(t))
	{
	}
};

template <typename T>
struct RectT
{
	T left = 0;
	T top = 0;
	T width = 0;
	T height = 0;

	RectT() = default;

	template <typename V>
	RectT(V l, V t, V w, V h) 
		: left(gsl::narrow_cast<T>(l))
		, top(gsl::narrow_cast<T>(t))
		, width(gsl::narrow_cast<T>(w))
		, height(gsl::narrow_cast<T>(h))
	{
	}

	RectT<T>& Union(RectT<T> const& rc)
	{		
		auto l = std::min<T>(rc.left, left);
		auto t = std::min<T>(rc.top, top);

		auto r = std::max<T>(rc.left + rc.width, left + width);
		auto b = std::max<T>(rc.top + rc.height, top + height);

		left = l;
		top = t;
		width = r - l;
		height = b - t;
		return *this;
	}

	static bool Equal(T const& a, T const& b)
	{
		return abs(a - b) <= std::numeric_limits<T>::epsilon();
	}

	bool operator==(RectT<T> const& rc) const
	{
		return Equal(rc.left, left) && Equal(rc.top, top) && Equal(rc.width, width) && Equal(rc.height, height);
	}
};

using PointD = PointT<double>;
using RectD = RectT<double>;
using RGBAColor = uint32_t;