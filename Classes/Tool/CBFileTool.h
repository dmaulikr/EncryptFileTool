#pragma once

#include <string>

class CBFileTool
{
public:

	static std::string getFullPath(const char* fileName);

	static bool isExistFile(const char* pFilePath);

	static std::string getFileData(const char* pFilePath);
    
    static bool saveToFile(const char* pData, const char* pFilePath);

	//只针对windows平台，如果文件夹不存在，自动创建文件夹
	static bool saveFileToFolder(const char* pData, const char* pFilePath);
};
