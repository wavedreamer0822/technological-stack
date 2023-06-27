#pragma once
#include "UnitGroupBase.h"
#include "ISolvableUnit.h"
#include "SolverTypes.h"

namespace LxCFD
{
    template <typename T>
    class SolvableUnitGroup : public UnitGroupBase<T>, public ISolvableUnit
    {
    public:
        SolverTypes SolverType = SolverTypes::AMGV;

        virtual void Solve_Steady() override
        {
            for (auto &u : UnitGroupBase<T>::Units)
            {
                u->Solve_Steady();
            }
        }

        virtual void Solve_ExplicitTransient() override
        {
            for (auto &u : UnitGroupBase<T>::Units)
            {
                u->Solve_ExplicitTransient();
            }
        }

        virtual void SaveOldValue() override
        {
            for (auto &u : UnitGroupBase<T>::Units)
            {
                u->SaveOldValue();
            }
        }

        virtual void Solve_ImplicitTransient() override
        {
            for (auto &u : UnitGroupBase<T>::Units)
            {
                u->Solve_ImplicitTransient();
            }
        }
    };
}