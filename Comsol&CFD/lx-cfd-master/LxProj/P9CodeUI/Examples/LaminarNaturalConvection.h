#pragma once
#include "ExampleBase.h"

namespace LxCFD
{
    class LaminarNaturalConvection : public ExampleBase
    {
    public:
        LaminarNaturalConvection(int ID, const std::string &fileFolder);
        virtual void RunCase() override;
    };
}