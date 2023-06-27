#pragma once
#include "MaterialData.h"
#include "PhysicalTypes.h"
#include "Value1Const.h"
namespace LxCFD
{
    class MaterialLib
    {
    public:
        std::unique_ptr<MaterialData> GetDefaultMaterial(PhysicalTypes physicalType)
        {
            switch (physicalType)
            {
            case PhysicalTypes::Solid:
            {
                std::unique_ptr<MaterialData> solid = std::unique_ptr<MaterialData>(new MaterialData());
                solid->Name = "ÂÁ";
                solid->Density = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(2700));
                solid->SpecificHeat = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(900));
                solid->ThermalConductivity = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(200));
                return std::move(solid);
            }
            case PhysicalTypes::Fluid:
            {
                std::unique_ptr<MaterialData> fluid = std::unique_ptr<MaterialData>(new MaterialData());
                fluid->Name = "¿ÕÆø";
                fluid->Density = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(1.2));
                fluid->ThermalConductivity = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(0.026));
                fluid->SpecificHeat = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(1000));
                fluid->Viscosity = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(1.8e-5));
                fluid->ThermalExpansionCoefficent = 0.0033;
                return std::move(fluid);
            }
            default:
                return nullptr;
            }
        }
    };
}