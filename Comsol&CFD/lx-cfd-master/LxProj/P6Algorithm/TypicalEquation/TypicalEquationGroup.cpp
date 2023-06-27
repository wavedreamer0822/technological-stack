#include "TypicalEquationGroup.h"

namespace LxCFD
{
    void TypicalEquationGroup::Rearrange(ConnectivityAnalysis &connectivityAnalysis)
    {
        Units.clear();
        auto pools = connectivityAnalysis.SplitByConnectivity(Equations, Connects);
        for (auto &l : pools)
        {
            auto u = std::unique_ptr<TypicalEquationUnit>(new TypicalEquationUnit());
            u->CreateUnit(l.Zones, l.Contacts, SolverType);
            Units.push_back(std::move(u));
        }
        Equations.clear();
        Connects.clear();
    }
}