#pragma once
#include "LinearSolver.h"
#include "EquationBase.h"
#include "ConnectBase.h"
#include "ISolvableUnit.h"

namespace LxCFD
{
    class TypicalEquationUnit : public LinearSolver, public ISolvableUnit
    {
    public:
        void CreateUnit(std::vector<EquationBase *> &scalars, std::vector<ConnectBase *> &connects, SolverTypes solverTypes);
        virtual void SaveOldValue() override;
        virtual void Solve_Steady() override;
        virtual void Solve_ExplicitTransient() override;
        virtual void Solve_ImplicitTransient() override;

    protected:
        std::vector<EquationBase *> Equations;
        std::vector<ConnectBase *> Connects;
        void prepareMatirx();
        void updateBounds();
    };
}