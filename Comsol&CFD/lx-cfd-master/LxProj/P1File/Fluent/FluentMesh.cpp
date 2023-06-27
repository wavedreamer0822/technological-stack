#include "FluentMesh.h"
#include "LxString.h"
namespace LxCFD
{
    void FluentMesh::ReadFile(const std::string &filePath)
    {
        ReadMeshFile(filePath);
        ConvertToMesh();
    }
    void FluentMesh::ReadMeshFile(const std::string &filePath)
    {
        if (!LxString::EndWith(filePath, ".msh"))
        {
            throw std::invalid_argument("文件格式不正确");
        }
        LxConsole::Info("开始读取网格……");
        StartReader(filePath, " ()");
        while (!Reader.eof())
        {
            ReadLine();
            if (LxString::StartWith(LineContent, "(10")) //点
            {
                if (SplitedLine.at(1) != "0")
                {
                    FlHead mp;

                    mp.SetHead(SplitedLine);
                    FlNodes->resize(mp.Index.GetCount());
                    if (!LxString::EndWith(LineContent, "("))
                    {
                        ReadLine();
                    }
                    for (std::size_t i = 0; i < FlNodes->size(); ++i)
                    {
                        ReadLine();
                        double x, y, z;
                        LxString::StringToDouble(x, SplitedLine.at(0));
                        LxString::StringToDouble(y, SplitedLine.at(1));
                        LxString::StringToDouble(z, SplitedLine.at(2));
                        FlNodes->at(i) = Vector3d(x, y, z);
                    }
                }
            }
            else if (LxString::StartWith(LineContent, "(12")) //zone
            {
                if (SplitedLine.at(1) != "0")
                {
                    std::unique_ptr<FlZone> zone(new FlZone());
                    zone->SetHead(SplitedLine);
                    FlZones.push_back(std::move(zone));
                }
            }
            else if (LxString::StartWith(LineContent, "(13")) //thread
            {
                if (SplitedLine.at(1) != "0")
                {
                    std::unique_ptr<FlThread> mt(new FlThread());
                    mt->SetHead(SplitedLine);
                    std::size_t size = mt->Index.GetCount();
                    mt->Faces.resize(size);
                    ShallowArrayStorage.Initialize(1, size);
                    for (std::size_t i = 0; i < size; i++)
                    {
                        ReadLine();
                        FlFace &f = mt->Faces.at(i);
                        f.Nodes = ShallowArrayStorage.Create(SplitedLine.size() - 2);
                        int i1 = 0;
                        for (; i1 < f.Nodes.GetLengh(); ++i1)
                        {
                            f.Nodes[i1] = std::stoi(SplitedLine.at(i1), 0, 16) - 1;
                        }
                        f.c0 = std::stoi(SplitedLine.at(i1), 0, 16) - 1;
                        f.c1 = std::stoi(SplitedLine.at(i1 + 1), 0, 16) - 1;
                    }
                    FlThreads.push_back(std::move(mt));
                }
            }
            else if (LxString::StartWith(LineContent, "(2"))
            {
                if (SplitedLine.at(1) == "2")
                {
                    throw std::invalid_argument("暂不支持二维网格");
                }
            }
            else if (LxString::StartWith(LineContent, "(39"))
            {
                int ID = std::stoi(SplitedLine.at(1));
                NameMesh(FlZones, ID);
                NameMesh(FlThreads, ID);
            }
        }
        EndReader();
        LxConsole::Info("完成读取网格。");
    }

}