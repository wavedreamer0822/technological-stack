#pragma once
#include "IJacobiSolvableZone.h"
#include "IBiCGStabSolvableZone.h"
#include "ICalResidual.h"
namespace LxCFD
{
   class ISolvableZone : public IJacobiSolvableZone, public IBiCGStabSolvableZone, public ICalResidual
   {
   };
}