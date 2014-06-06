#pragma once

#include <string>

class CBFileTool
{
public:

	static std::string getFullPath(const char* fileName);

	static bool isExistFile(const char* pFilePath);

	static std::string getFileData(const char* pFilePath);
    
    static bool saveToFile(const char* pData, const char* pFilePath);

	//ֻ���windowsƽ̨������ļ��в����ڣ��Զ������ļ���
	static bool saveFileToFolder(const char* pData, const char* pFilePath);
};
