#include "AsciiLineReader.h"
#include "LxTool.h"
#include "LxString.h"
#include "LxConsole.h"
namespace LxCFD
{
    void AsciiLineReader::ReadLine()
    {
        ++LineNum;
        std::getline(Reader, LineContent);
        LxString::Split(SplitedLine, LineContent, SplitChar);
        //std::cout << LineNum << std::endl;
    }
    void AsciiLineReader::StartReader(const std::string &filePath, const std::string &splitChar)
    {
        LineNum = 0;
        Reader.open(filePath, std::ios::in);
        if (!Reader.is_open())
        {
            throw std::invalid_argument("无法打开文件");
        }
        SplitChar = splitChar;
    }
    void AsciiLineReader::EndReader()
    {
        Reader.close();
        LineContent = "";
        SplitedLine.clear();
        SplitChar.clear();
        if (LineNum == 0)
        {
            throw std::invalid_argument("空文件");
        }
    }
}