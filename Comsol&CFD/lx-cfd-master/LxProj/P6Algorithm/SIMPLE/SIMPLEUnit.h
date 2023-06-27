#pragma once
#include "SIMPLEBase.h"
namespace LxCFD
{
    class SIMPLEUnit : public SIMPLEBase
    {
    protected:
        int MaxNonOrthCorSteps = 1;
        virtual void solvePCors() override;
    };
}