#pragma once
#include "ExampleBase.h"
namespace LxCFD
{
    class SolidCubeCase : public ExampleBase
    {
    public:
        SolidCubeCase(int ID,const std::string &fileFolder);
        virtual void RunCase() override;
    };
}