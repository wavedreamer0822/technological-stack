#pragma once
#include <iostream>
#include <fstream>
#include "IWriteFile.h"
namespace LxCFD
{
    class XMLWriter 
    {
    protected:
        std::ofstream Writer;
        std::string Space;
        bool StartWriter(const std::string &filePath);
        bool EndWriter();
        void WriteXmlHead(const std::string &str);
        void WriteXmlEnd(const std::string &str);
        void WriteSpaceEnter(int index, int interval);
    };
}