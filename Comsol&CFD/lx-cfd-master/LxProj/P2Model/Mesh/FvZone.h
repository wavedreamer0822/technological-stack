#pragma once
#include "FvZoneBase.h"
#include "ZoneCFDFields.h"
namespace LxCFD
{
    class FvZone : public FvZoneBase
    {
    public:
        std::shared_ptr<PhysicalModel> PhysicalModel=nullptr;;
        std::unique_ptr<Value1Base<double>> EnergySource=std::unique_ptr<Value1Const::Double>(new Value1Const::Double(0));
        ZoneCFDFields CFDFields;
    };
}