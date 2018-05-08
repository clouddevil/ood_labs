#pragma once


class IPainter
{
public:
	virtual void DrawPicture(CPictureDraft const& draft, ICanvas& canvas) = 0;
};