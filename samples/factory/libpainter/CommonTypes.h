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

};

using PointD = PointT<double>;
using RectD = RectT<double>;
using RGBAColor = uint32_t;