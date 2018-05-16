#pragma once
#include "CommonTypes.h"


RectD CalcuateBounds(std::initializer_list<PointD> const& pts);

PointD MovePoint(PointD const& pt, RectD const& frame, RectD const& newFrame);

RectD MoveRect(RectD const& rc, RectD const& frame, RectD const& newFrame);


