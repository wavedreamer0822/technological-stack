#pragma once
#include <string>
namespace LxCFD
{
    class IReadFile
    {
    public:
        virtual void ReadFile(const std::string &filePath) = 0;
    };
}