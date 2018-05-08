#pragma once

class ICanvas;
class IPictureDraft;

using IPainter = std::function<void(IPictureDraft const& draft, ICanvas& canvas)>;
