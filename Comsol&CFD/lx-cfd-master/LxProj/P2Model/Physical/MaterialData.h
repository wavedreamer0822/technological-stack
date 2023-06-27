#pragma once
#include <memory>
#include <string>
#include "Value1Base.h"
#include "PhysicalTypes.h"
namespace LxCFD
{
   class MaterialData
   {
   public:
      std::string Name;
      PhysicalTypes PhysicalType;
      std::unique_ptr<Value1Base<double>> Density;
      std::unique_ptr<Value1Base<double>> SpecificHeat;
      std::unique_ptr<Value1Base<double>> ThermalConductivity;
      std::unique_ptr<Value1Base<double>> Viscosity;
      double ThermalExpansionCoefficent;
   };
}