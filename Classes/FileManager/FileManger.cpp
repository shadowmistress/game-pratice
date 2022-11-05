#include "FileManger.h"

std::string  FileManager::getFileDebugPath() 
{
    std::string resPaths = (FileUtils::getInstance()->getSearchPaths().at(0));
    std::vector<std::string> v1 = regx.split(resPaths, "/");
    std::string debugPaths = "";
    for (int i = 0; i < v1.size() - 2; i++)
        debugPaths = debugPaths + v1.at(i).append("//");
	return debugPaths;
}
std::string  FileManager::getFileMapPath()
{
    std::string resPaths = (FileUtils::getInstance()->getSearchPaths().at(0));
    return resPaths.append("Map/map.json");
}
std::string FileManager::getFileTextPath()
{
    std::string resPaths = (FileUtils::getInstance()->getSearchPaths().at(0));
    return resPaths.append("Text/");
}
void FileManager::outPutDebugLog(std::string message)
{

}

std::string FileManager::getFilePreLoadPath()
{
    std::string resPaths = (FileUtils::getInstance()->getSearchPaths().at(0));
    return resPaths.append("Map/preLoad.json");
}

std::string FileManager::getFileResPath()
{
    std::string resPaths = (FileUtils::getInstance()->getSearchPaths().at(0));
    return resPaths.append("Map/");
}