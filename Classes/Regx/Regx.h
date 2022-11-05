#pragma once
#include<iostream>
#include<string>
#include <fstream>
#include<vector>
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"

class Regx
{
public:
	Regx();
	std::vector<std::string> split(std::string str, std::string pattern);
	std::string& replace_all(std::string& src, const std::string& old_value, const std::string& new_value);
    std::string getJsonData(std::string filename, std::string vaule1,int tag,std::string vaule2);
	std::string getJsonData(std::string filename, std::string vaule);
	~Regx();
private:
	std::string::size_type pos;
};