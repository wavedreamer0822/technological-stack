#pragma once
#include "FvContactBase.h"
#include "FvZone.h"
#include "ContactCFDFields.h"

namespace LxCFD
{
    class FvContact : public FvContactBase
    {
    public:
        ContactCFDFields CFDFields;
        std::unique_ptr<ValueBase<double>> EnergySource = std::unique_ptr<ValueBase<double>>(new Value1Const::Double(0));
        std::unique_ptr<Value1Base<double>> ThermalConductivity = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(1));
        std::unique_ptr<Value1Base<double>> Thickness = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(0));
    };
}