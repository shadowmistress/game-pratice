#pragma once
#include<iostream>
#include<string>
#include<vector>
class Regx
{
public:
	std::vector<std::string> split(std::string str, std::string pattern);
	std::string& replace_all(std::string& src, const std::string& old_value, const std::string& new_value);

private:
	std::string::size_type pos;
};