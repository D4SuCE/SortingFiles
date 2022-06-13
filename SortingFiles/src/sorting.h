#pragma once

#include <string>
#include <iostream>
#include <Windows.h>
#include <filesystem>

namespace Sort
{
	size_t numberFiles(std::string path)
	{
		size_t counter = 0;
		for (const auto& file : std::filesystem::directory_iterator(path))
		{
			if (!std::filesystem::is_directory(file))
			{
				counter++;
			}
		}
		return counter;
	}

	void Files(std::string path)
	{
		if (!std::filesystem::exists(path))
		{
			std::cerr << path << ": not found!" << std::endl;
			return;
		}
		else if (!std::filesystem::is_directory(path))
		{
			std::cerr << path << ": is not directory!" << std::endl;
			return;
		}

		std::cout << "Path: " << path << std::endl;

		std::cout << "Total files: " << numberFiles(path) << std::endl;

		if (numberFiles(path) != 0)
		{
			std::cout << "Sorting started" << std::endl;

			size_t counter = 0;

			for (const auto& file : std::filesystem::directory_iterator(path))
			{
				if (!std::filesystem::is_directory(file))
				{
					std::string extension = file.path().extension().string().erase(0, 1);
					std::string path_to = path + "\\" + extension + "\\" + file.path().filename().string();
					std::string path_from = path + "\\" + file.path().filename().string();

					std::filesystem::create_directory(path + "\\" + extension);
					MoveFileA(path_from.c_str(), path_to.c_str());

					std::cout << "#File: " << ++counter << std::endl;
				}
			}
			std::cout << "Sorting finished" << std::endl;
		}		
	}
}