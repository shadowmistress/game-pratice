#include "Regx.h"
std::vector<std::string>  Regx::split(std::string str, std::string pattern) 
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;//扩展字符串以方便操作
    int size = str.size();
    for (int i = 0; i < size; i++)
    {
        pos = str.find(pattern, i);
        if (pos < size)
        {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

std::string&  Regx::replace_all(std::string& src, const std::string& old_value, const std::string& new_value) {
    // 每次重新定位起始位置，防止上轮替换后的字符串形成新的old_value
    for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length()) {
        if ((pos = src.find(old_value, pos)) != std::string::npos) {
            src.replace(pos, old_value.length(), new_value);
        }
        else break;
    }
    return src;
}