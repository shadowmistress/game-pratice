#include "Regx.h"

Regx::Regx() 
{
}


/***********************************************************************
Name : split()
Function : Split string value by appoint characters.
Args:
    string str     :  string vaule need by split.
    string pattern :  appoint characters.
return type :vector<string>, value : Characters which has be split;
************************************************************************/
std::vector<std::string>  Regx::split(std::string str, std::string pattern) 
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;
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


/***********************************************************************
Name : replace_all()
Function :Replace string value about the part of characters by appoint characters.
Args:
    string& src       :  src string vaule.
    string& old_value :  string vaule use for replace src string value.
    string& new_value : new string value who is be replace.
return type :string, value : string value who is be replace.
************************************************************************/
std::string&  Regx::replace_all(std::string& src, const std::string& old_value, const std::string& new_value) {
    // 
    for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length()) {
        if ((pos = src.find(old_value, pos)) != std::string::npos) {
            src.replace(pos, old_value.length(), new_value);
        }
        else 
            break;
    }
    return src;
}


/***********************************************************************
Name : getJsonData()
Function : Parse json data and  return result.json mode is string.
Args:
    string filename   : file path.
    string vaule      : Parse input value.
return type :string   :value : result json parsed,error(parse fail)
************************************************************************/
std::string Regx::getJsonData(std::string filename, std::string vaule)
{
    std::string ret = "false";
    std::ifstream in(filename);
    if (!in.is_open()) {
        fprintf(stderr, "fail to read json file: %s\n", filename);
        return "error";
    }
    std::string json_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();
    rapidjson::Document dom;
    if (!dom.Parse(json_content.c_str()).HasParseError())
    {
        if (dom.HasMember(vaule.c_str()) && dom[vaule.c_str()].IsString())
        {
            ret = dom[vaule.c_str()].GetString();
        }
    }
    return ret;
}


/***********************************************************************
Name : getJsonData()
Function : Parse json data and  return result.json mode is object.
Args:
    string filename   : File path.
    int tag           ; The part of date in the array.
    string vaule      : Parse input value.
return type :string   : Value : result json parsed,error(parse fail)
************************************************************************/
std::string Regx::getJsonData(std::string filename, std::string vaule1,int tag, std::string vaule2)
{
    std::string ret = "error";
    std::ifstream in(filename);
    if (!in.is_open()) {
        fprintf(stderr, "fail to read json file: %s\n", filename);
        return "error";
    }
    std::string json_content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();

    rapidjson::Document dom;
    if (!dom.Parse(json_content.c_str()).HasParseError()) 
    {
        if (dom.HasMember(vaule1.c_str()) && dom[vaule1.c_str()].IsArray())
        {
            const rapidjson::Value& arr = dom[vaule1.c_str()];
            if (arr.Size() < tag)
            {
                cocos2d::log("search tag beyond json list");
            }
            else
            {
                if (arr[tag].IsObject())
                {
                    const rapidjson::Value& obj = arr[tag];
                    if (obj.HasMember(vaule2.c_str()) && obj[vaule2.c_str()].IsString())
                    {
                        ret = obj[vaule2.c_str()].GetString();
                    }
                }
            }
        }
    }
    return ret;
}

Regx::~Regx()
{

}