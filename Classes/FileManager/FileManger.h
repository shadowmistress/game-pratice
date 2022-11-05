#pragma once
#include "cocos2d.h"
#include "Regx/Regx.h"
USING_NS_CC;

class FileManager
{
public:
	std::string getFileDebugPath();
	std::string getFileMapPath();
	std::string getFilePreLoadPath();
	std::string getFileTextPath();
	std::string getFileResPath();
	void outPutDebugLog(std::string message);

private:
	
	Regx regx;
};
