#pragma once
#include <string>
#include <typeinfo>
#include "AppRes.h"
namespace LxCFD
{
    class ExampleBase
    {
    public:
        ExampleBase(int ID, const std::string &fileFolder);
        int ID;
        std::string FileFolder;
        std::string Description;
        virtual void RunCase() = 0;
        FvZone &FineZone(const std::string &zoneName);
        FvThread &FindThread(FvZone &zone, const std::string &threadName);
        FvContact &FineContact(const std::string &contactName);
    };
}