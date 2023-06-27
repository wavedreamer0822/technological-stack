#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace LxCFD
{
    class AsciiLineReader
    {
    public:
        std::ifstream Reader;
        std::string SplitChar;
        int LineNum = 0;
        std::string LineContent;
        std::vector<std::string> SplitedLine;
        void ReadLine();
        void StartReader(const std::string &filePath,const std::string &splitChar);
        void EndReader();
    };
}