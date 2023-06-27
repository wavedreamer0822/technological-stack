#include "LinearSolver.h"

namespace LxCFD
{
    void LinearSolver::SetAMGSolver(std::vector<AMGInZone *> &AMGsInZone, std::vector<AMGInContact *> &AMGsInContact)
    {
        for (auto &z : AMGsInZone)
        {
            addAMGSolver(z);
        }
        for (auto &c : AMGsInContact)
        {
            addAMGSolver(c);
        }
    }
    void LinearSolver::addAMGSolver(AMGInZone *AMG)
    {
        if (AMG->MaxCoarseLevel > MaxCoarseLevel)
        {
            MaxCoarseLevel = AMG->MaxCoarseLevel;
        }
        AMGsInZone.push_back(AMG);
        if (VariableCount.size() != AMG->MgZones.size())
        {
            VariableCount.resize(AMG->MgZones.size());
        }
        for (std::size_t i1 = 0; i1 < VariableCount.size(); ++i1)
        {
            VariableCount.at(i1) += AMG->MgZones.at(i1)->InnerIndex.CellIDs.GetCount();
        }
    }
    void LinearSolver::addAMGSolver(AMGInContact *amg)
    {
        AMGsInContact.push_back(amg);
    }
}