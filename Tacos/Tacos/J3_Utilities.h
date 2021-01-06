#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>

/// <summary>
/// Displays a list of all the files in the current working directory as strings
/// </summary>
/// <param name="path">Path to the specified directory</param>
void ListDirectoryContents(std::filesystem::path path) {
	for (const auto& entry : std::filesystem::directory_iterator(path))
		std::cout << entry.path() << std::endl;

	return;
}

/// <summary>
/// Returns the path to the current working directory
/// </summary>
/// <returns></returns>
std::filesystem::path CurrentDirectoryPath() {
	return std::filesystem::current_path();
}

void DoesFileExist(std::string strFullFilename) {
	std::ifstream ifile{};
	ifile.open(strFullFilename);
	if (ifile) {
		std::cout << "file " << strFullFilename << " exists" << std::endl;
	}
	else {
		std::cout << "file " << strFullFilename << " does not exist in " << CurrentDirectoryPath() << std::endl;
	}
	ifile.close();
}

