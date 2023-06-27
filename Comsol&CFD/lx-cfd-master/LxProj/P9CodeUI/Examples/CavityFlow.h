#pragma once
#include "ExampleBase.h"
namespace LxCFD
{
    class CavityFlow : public ExampleBase
    {
    public:
        CavityFlow(int ID, const std::string &fileFolder);
        virtual void RunCase() override;
    };
}