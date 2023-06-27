#pragma once
#include <string>

namespace LxCFD
{
    class IWriteFile
    {
    public:
        virtual bool WriteFile(const std::string &filePath) = 0;
    };
}