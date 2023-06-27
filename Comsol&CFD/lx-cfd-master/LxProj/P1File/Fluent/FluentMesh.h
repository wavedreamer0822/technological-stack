#pragma once
#include "AsciiLineReader.h"
#include "FluentMeshBase.h"
#include "IReadFile.h"

namespace LxCFD
{
    class FluentMesh : protected FluentMeshBase, public IReadFile, protected AsciiLineReader
    {
    public:
        virtual void ReadFile(const std::string &filePath) override;

    protected:
        void ReadMeshFile(const std::string &filePath);
        template <typename T>
        bool NameMesh(std::vector<T> &meshs, int ID)
        {
            for (auto &t : meshs)
            {
                if (t->ID == ID)
                {
                    t->Name = SplitedLine.at(3);
                    t->FlType = SplitedLine.at(2);
                    return true;
                }
            }
            return false;
        }
    };
}