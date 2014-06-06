#include "CBFolderTool.h"
#include "cocos2d.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <io.h>
#else
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#endif


std::vector<std::string> CBFolderTool::AllFilePathInFolder( std::string folderPath, int depth /*= 0*/ )
{
	std::vector<std::string> vecPath;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_finddata_t FileInfo;
	std::string strfind = folderPath + "\\*";
	long Handle = _findfirst(strfind.c_str(), &FileInfo);
	if (Handle == -1L)
	{
		cocos2d::CCLog("can not match the folder path");
		return vecPath;
	}
	do
	{
		//判断是否有子目录
		if (FileInfo.attrib & _A_SUBDIR)    
		{
			//这个语句很重要
			if( (strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0))   
			{
				std::string newPath = folderPath + "\\" + FileInfo.name;
				std::vector<std::string> vecTmp = AllFilePathInFolder(newPath);
				vecPath.insert(vecPath.end(), vecTmp.begin(), vecTmp.end());
			}
		}
		else  
		{
			std::string filename = (folderPath + "\\" + FileInfo.name);
			vecPath.push_back(filename);
		}
	}while(_findnext(Handle, &FileInfo) == 0);
	_findclose(Handle);

#else
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(folderPath.c_str())) == NULL)
	{
		cocos2d::CCLog("cannot open directory: %s\n", folderPath.c_str());
		return vecPath;
	}
	chdir(folderPath.c_str());
	while((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode))
		{

			if((strcmp(".",entry->d_name) == 0) || (strcmp("..",entry->d_name) == 0))
				continue;

			std::vector<std::string> vecTmp = AllFilePathInFolder(entry->d_name, depth+4);
			vecPath.insert(vecPath.end(), vecTmp.begin(), vecTmp.end());
		}
		else
		{
			std::string filename = entry->d_name;
			vecPath.push_back(filename);
		}
	}
	chdir("..");
	closedir(dp);

#endif

	return vecPath;
}
