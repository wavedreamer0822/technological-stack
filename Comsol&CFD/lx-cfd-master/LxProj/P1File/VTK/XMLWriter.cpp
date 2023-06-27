#include "XMLWriter.h"
#include "LxConsole.h"
namespace LxCFD
{
    bool XMLWriter::StartWriter(const std::string &filePath)
    {
        Writer.open(filePath, std::ios::out);
        if (!Writer.is_open())
        {
            LxConsole::Error("写出文件时无法打开目标文件");
            return false;
        }
        Writer << "<?xml version=\"1.0\"?>" << std::endl;
        Space.clear();
        return true;
    }
    bool XMLWriter::EndWriter()
    {
        Writer.close();
        return true;
    }
    void XMLWriter::WriteXmlHead(const std::string &str)
    {
        Writer << Space << str << std::endl;
        Space.append("  ");
    }
    void XMLWriter::WriteXmlEnd(const std::string &str)
    {
        Space.erase(Space.size() - 2);
        Writer << Space << str << std::endl;
    }
    void XMLWriter::WriteSpaceEnter(int index, int interval)
    {
        if (index % interval == 0)
        {
            if (index == 0)
            {
                Writer << Space;
            }
            else
            {
                Writer << std::endl
                       << Space;
            }
        }
    }
}