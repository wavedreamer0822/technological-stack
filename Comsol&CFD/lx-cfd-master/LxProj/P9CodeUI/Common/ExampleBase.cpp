#include "ExampleBase.h"

namespace LxCFD
{
    ExampleBase::ExampleBase(int ID, const std::string &fileFolder) : ID(ID), FileFolder(fileFolder)
    {
    }
    FvZone &ExampleBase::FineZone(const std::string &zoneName)
    {
        for (auto &z : AppRes::FvMesh->Zones)
        {
            if (z->Name == zoneName)
            {
                return *z;
            }
        }
        std::stringstream ss;
        ss << "未找到" << zoneName << "对应的区域";
        throw std::invalid_argument(ss.str());
    }
    FvThread &ExampleBase::FindThread(FvZone &zone, const std::string &threadName)
    {
        for (auto &z : zone.BoundThreads)
        {
            if (z->Name == threadName)
            {
                return *z;
            }
        }
        std::stringstream ss;
        ss << "未找到" << threadName << "对应的界面";
        throw std::invalid_argument(ss.str());
    }
    FvContact &ExampleBase::FineContact(const std::string &contactName)
    {
        for (auto &z : AppRes::FvMesh->Contacts)
        {
            if (z->Name == contactName)
            {
                return *z;
            }
        }
        std::stringstream ss;
        ss << "未找到" << contactName << "对应的接触面";
        throw std::invalid_argument(ss.str());
    }
}