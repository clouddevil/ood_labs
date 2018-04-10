#pragma once
#include "IOutputDataStream.h"


class FileOutputStream
	: public IOutputDataStream
{
public:
	FileOutputStream();
	~FileOutputStream();
};

