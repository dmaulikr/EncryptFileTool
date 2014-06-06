#include "CBFileTool.h"
#include "cocos2d.h"
#include <iostream>

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <io.h>
#include <direct.h>
#endif


std::string CBFileTool::getFullPath( const char* fileName )
{
	std::string filePath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
	return filePath;
}

bool CBFileTool::isExistFile( const char* pFilePath )
{
	if (cocos2d::CCFileUtils::sharedFileUtils()->isFileExist(pFilePath))
	{
		return true;
	}
	return false;
}

std::string CBFileTool::getFileData( const char* pFilePath )
{
	std::string strRet = "";

	unsigned long size = 0;
	char* pBuffer = (char*)cocos2d::CCFileUtils::sharedFileUtils()->getFileData(pFilePath, "rt" , &size);
	if (pBuffer != NULL && size > 0)
	{
		std::string strTmp = (char*)pBuffer;
		strRet = strTmp.substr(0, size);
	}
	CC_SAFE_DELETE_ARRAY(pBuffer);
	return strRet;
}

bool CBFileTool::saveToFile( const char* pData, const char* pFilePath )
{
	//创建一个文件指针
	FILE* file = fopen(pFilePath, "w+");
	if (file)
	{
		fputs(pData, file);
		fclose(file);
		return true;
	}

	return false;
}

bool CBFileTool::saveFileToFolder( const char* pData, const char* pFilePath )
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	//创建一个文件指针
	FILE* file = fopen(pFilePath, "w+");
	if(!file)
	{
		std::string path = pFilePath;
		std::string::size_type pos = path.find("/");
		while(pos != std::string::npos)
		{
			//找出目录路径
			std::string strDir = path.substr(0, pos);
			//判断目录是否存在
			if(_access(strDir.c_str(), 0) == -1)
			{
				//新建目录
				_mkdir(strDir.c_str());
			}

			pos = path.find("/", pos+1);
		}
		file = fopen(pFilePath, "w+");
	}

	if (file)
	{
		fputs(pData, file);
		fclose(file);
		return true;
	}

	return false;

#else
	return true;

#endif
}
