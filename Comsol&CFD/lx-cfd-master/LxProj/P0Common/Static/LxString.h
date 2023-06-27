#pragma once
#include <string>
#include <sstream>
#include <vector>
namespace LxCFD
{
    class LxString
    {
    public:
        static void Replace(std::string &targetString, const std::string &oldStr, const std::string &newStr);
        static bool StringToDouble(double &out_result, const std::string &inputStr);
        static void Split(std::vector<std::string> &out_SplitedString,const std::string &inputString, char splitChar);
        static void Split(std::vector<std::string> &out_SplitedString,const std::string &inputString, const std::string &splitChars);
        static std::string &Trim(std::string &targetString);
        static bool StartWith(const std::string &targetString, const std::string &compareStart);
        static bool EndWith(const std::string &targetString, const std::string &compareEnd);
    };
}