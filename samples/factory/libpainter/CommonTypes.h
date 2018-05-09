#pragma once

template <typename T>
struct PointT
{
	T x = 0;
	T y = 0;
};

template <typename T>
struct RectT
{
	T left;
	T top;
	T width;
	T height;
};

using PointD = PointT<double>;
using RectD = RectT<double>;
using RGBAColor = uint32_t;