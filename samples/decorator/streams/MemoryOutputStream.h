#pragma once
#include "IOutputDataStream.h"

class MemoryOutputStream
	: public IOutputDataStream
{
public:
	MemoryOutputStream();
	~MemoryOutputStream();
};

