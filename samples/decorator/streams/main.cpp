#include "stdafx.h"
#include "FileInputStream.h"
#include "FileOutputStream.h"
#include "RLEOutputStream.h"
#include "RLEInputStream.h"
#include "TransformedInputStream.h"
#include "CaesarCipherTransform.h"
#include "TransformedOutputStream.h"

void make_lab(std::vector<std::string> commands)
{
	IOutputDataStreamPtr os = std::make_shared<FileOutputStream>(commands.back());
	commands.pop_back();

 	IInputDataStreamPtr is = std::make_shared<FileInputStream>(commands.back()); 	
	commands.pop_back();

	auto GetKey = [&](uint32_t index)
	{
		if (index < commands.size())
		{
			return commands[index];
		}
		throw std::invalid_argument("invalid command argument");
	};


	uint32_t index = 0;
	for (uint32_t i = 0; i < commands.size(); ++i)
	{
		auto const& cmd = GetKey(i);
		if (cmd == "--compress")
		{			
			os = std::make_shared<RLEOutputStream>(os);
		}
		else if (cmd == "--decompress")
		{
			is = std::make_shared<RLEInputStream>(is);
		}
		else if (cmd == "--decrypt")
		{
			auto key = std::stoi(GetKey(++i));
			auto transform = std::make_shared<CaesarCipherTransform>(true, key);
			is = std::make_shared<TransformedInputStream>(is, transform);
		}
		else if (cmd == "--encrypt")
		{
			auto key = std::stoi(GetKey(++i));
			auto transform = std::make_shared<CaesarCipherTransform>(false, key);
			is = std::make_shared<TransformedInputStream>(is, transform);
			//os = std::make_shared<TransformedOutputStream>(os, transform);
		}
		else
		{
			std::cout << cmd << " command skipped" << std::endl;
		}
	}

	std::vector<uint8_t> buffer(64);
	while (!is->IsEOF())
	{
		auto size = is->ReadBlock(buffer.data(), buffer.size());
		os->WriteBlock(buffer.data(), size);
	}
}

int main(int argc, char* argv[])
{
	try
	{
		if (argc < 3)
		{
			throw std::runtime_error("invalid arguments count");
		}

		auto index = 1;
		std::vector<std::string> args;
		while (index < argc)
		{			
			args.push_back(argv[index++]);
		}

		//make_lab(args);

		std::vector<std::string> toOut{ "--encrypt", "3", "--encrypt",  "100500",  "--compress",  "input.txt", "output.txt" };
		make_lab(toOut);

		std::vector<std::string> toIn{ "--decompress", "--decrypt", "100500",  "--decrypt",  "3", "output.txt",  "input.txt.restored" };
		make_lab(toIn);
	}
	catch (std::exception const& e)
	{
		std::cout << e.what();
	}

	return 0;
}
