#pragma once
#include "SolvableUnitGroup.h"
#include "SIMPLEBase.h"
namespace LxCFD
{
    class SIMPLEGroup : public SolvableUnitGroup<SIMPLEBase>
    {
    public:
        std::vector<PressureCorrectionBasic *> SIMPLEs;
        std::vector<ConnectBase *> Connects;
        virtual void Rearrange(ConnectivityAnalysis &connectivityAnalysis) override;
    };
}