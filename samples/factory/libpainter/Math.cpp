#include "stdafx.h"
#include "Math.h"

RectD CalcuateBounds(std::initializer_list<PointD> const& pts)
{
	std::set<double> xs;
	std::set<double> ys;
	for (auto& p : pts)
	{
		xs.insert(p.x);
		ys.insert(p.y);
	}
	auto left = *xs.begin();
	auto right = *xs.rbegin();
	auto top = *xs.begin();
	auto bottom = *xs.rbegin();

	return RectD{ left, top, right - left, bottom - top };
}

PointD MovePoint(PointD const& pt, RectD const& frame, RectD const& newFrame)
{
	auto x = (frame.width > 0) ? ((pt.x - frame.left) / frame.width) : 0;
	auto y = (frame.height > 0) ? ((pt.y - frame.top) / frame.height) : 0;
	return { newFrame.left + x * newFrame.width,  newFrame.top + y * newFrame.height };
}

RectD MoveRect(RectD const& rc, RectD const& frame, RectD const& newFrame)
{
	PointD leftTop{ rc.left, rc.top };
	auto lt = MovePoint(leftTop, frame, newFrame);

	PointD rightBottom{ rc.left + rc.width, rc.top + rc.height };
	auto rb = MovePoint(rightBottom, frame, newFrame);
	
	return {lt.x, lt.y, rb.x - lt.x, rb.y - lt.y};
}
