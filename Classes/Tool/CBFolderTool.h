#pragma once

#include <string>
#include <vector>

class CBFolderTool
{
public:

	static std::vector<std::string> AllFilePathInFolder(std::string folderPath, int depth = 0);
};