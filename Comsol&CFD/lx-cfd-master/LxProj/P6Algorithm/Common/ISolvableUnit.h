#pragma once

namespace LxCFD
{
    class ISolvableUnit
    {
        virtual void Solve_Steady() = 0;
        virtual void Solve_ExplicitTransient() = 0;
        virtual void SaveOldValue() = 0;
        virtual void Solve_ImplicitTransient() = 0;
    };
}