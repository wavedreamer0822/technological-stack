#pragma once
#include "SolvableUnitGroup.h"
#include "TypicalEquationUnit.h"
#include "ConnectBase.h"
namespace LxCFD
{
   class TypicalEquationGroup : public SolvableUnitGroup<TypicalEquationUnit>
   {
   public:
      std::vector<EquationBase *> Equations;
      std::vector<ConnectBase *> Connects;
      virtual void Rearrange(ConnectivityAnalysis &connectivityAnalysis) override;
   };
}