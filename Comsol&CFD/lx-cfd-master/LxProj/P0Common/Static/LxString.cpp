#include "LxString.h"
#include <cmath>
#include <iostream>
#include <string>
#include <cstring>
namespace LxCFD
{

    void LxString::Replace(std::string &targetString, const std::string &oldStr, const std::string &newStr)
    {
        std::string::size_type pos = 0;                //位置
        std::string::size_type oldlen = oldStr.size(); //要替换的字符串大小
        std::string::size_type newlen = newStr.size(); //目标字符串大小
        while ((pos = targetString.find(oldStr, pos)) != std::string::npos)
        {
            targetString.replace(pos, oldlen, newStr);
            pos += newlen;
        }
    }
    bool LxString::StringToDouble(double &out_result, const std::string &inputStr)
    {
        char *p = nullptr;
        out_result = strtod(inputStr.c_str(), &p);
        return out_result != HUGE_VAL && *p == '\0';
    }
    void LxString::Split(std::vector<std::string> &out_SplitedString, const std::string &inputString, char splitChar)
    {
        out_SplitedString.clear();
        std::stringstream input(inputString);
        std::string temp;
        while (std::getline(input, temp, splitChar))
        {
            if (!temp.empty())
            {
                out_SplitedString.push_back(temp);
            }
        }
    }
    void LxString::Split(std::vector<std::string> &out_SplitedString, const std::string &inputString, const std::string &splitChars)
    {
        out_SplitedString.clear();
        size_t last = 0;
        size_t index;
        do
        {
            index = inputString.find_first_of(splitChars, last);
            std::string temp = inputString.substr(last, index - last);
            if (!temp.empty())
            {
                out_SplitedString.push_back(temp);
            }
            last = index + 1;
        } while (index != std::string::npos);
    }
    std::string &LxString::Trim(std::string &targetString)
    {
        if (targetString.empty())
        {
            return targetString;
        }
        targetString.erase(0, targetString.find_first_not_of(" \t"));
        targetString.erase(targetString.find_last_not_of(" \t") + 1);
        return targetString;

        // //find the first position of not start with space or '\t'
        // std::string::size_type pos_begin = targetString.find_first_not_of(" \t");
        // if (pos_begin == std::string::npos)
        //     return targetString;

        // //find the last position of end with space or '\t'
        // std::string::size_type pos_end = targetString.find_last_not_of(" \t");
        // if (pos_end == std::string::npos)
        //     return targetString;

        // targetString = targetString.substr(pos_begin, pos_end - pos_begin);
    }
    bool LxString::StartWith(const std::string &targetString, const std::string &compareStart)
    {
        return strncmp(targetString.c_str(), compareStart.c_str(), compareStart.length()) == 0;
        // int srclen = targetString.size();
        // int startlen = compareStart.size();
        // if (srclen >= startlen)
        // {
        //     std::string temp = targetString.substr(0, startlen);
        //     if (temp == compareStart)
        //         return true;
        // }
        // return false;
    }
    bool LxString::EndWith(const std::string &targetString, const std::string &compareEnd)
    {
        int tarLength = targetString.size();
        int endLength = compareEnd.size();
        if (tarLength >= endLength)
        {
            std::string temp = targetString.substr(tarLength - endLength, endLength);
            if (temp == compareEnd)
                return true;
        }
        return false;
    }
}