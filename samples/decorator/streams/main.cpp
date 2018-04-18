#include "stdafx.h"
#include "FileInputStream.h"
#include "FileOutputStream.h"

int main(int argc, char* argv[])
{
	try
	{
		if (argc < 3)
		{
			throw std::runtime_error("invalid arguments count");
		}

		auto argIndex = argc - 1;
		const auto outputFileName = argv[argIndex--];
		const auto inputFileName = argv[argIndex--];

		auto inputStream = std::make_unique<FileInputStream>(inputFileName);
		auto outputStream = std::make_unique<FileOutputStream>(outputFileName);

		while (argIndex > 0)
		{

		}
	}
	catch (std::exception const& e)
	{
		std::cout << e.what();
	}

	return 0;
}
