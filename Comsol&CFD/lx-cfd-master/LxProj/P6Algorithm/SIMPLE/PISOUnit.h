#pragma once
#include "SIMPLEUnit.h"
namespace LxCFD
{
    class PISOUnit : public SIMPLEUnit
    {
    public:
        virtual void Solve_Steady() override;
        virtual void Solve_ImplicitTransient() override;

    protected:
        volatile int MaxPISOSteps = 1;
    };
}