#pragma once
#include "ExampleBase.h"
namespace LxCFD
{
    class TwoCubeCase : public ExampleBase
    {
    public:
        TwoCubeCase(int ID,const std::string &fileFolder);
        virtual void RunCase() override;
    };
}