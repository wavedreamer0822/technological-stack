#include "SIMPLEGroup.h"
#include "PISOUnit.h"
namespace LxCFD
{
    void SIMPLEGroup::Rearrange(ConnectivityAnalysis &connectivityAnalysis)
    {
        Units.clear();
        auto list = connectivityAnalysis.SplitByConnectivity(SIMPLEs, Connects);
        for (auto &l : list)
        {
            std::unique_ptr<SIMPLEBase> u; //= new SIMPLEBaseUnit();
            if (l.Zones.at(0)->SIMPLEMethod == SIMPLEMethods::PISO)
            {
                u = std::unique_ptr<PISOUnit>(new PISOUnit());
            }
            else
            {
                u = std::unique_ptr<SIMPLEUnit>(new SIMPLEUnit());
            }
            //u = std::unique_ptr<SIMPLEBase>(new SIMPLEBase());
            u->CreateUnit(l.Zones, l.Contacts, SolverType);
            Units.push_back(std::move(u));
        }
        SIMPLEs.clear();
        Connects.clear();
    }
}