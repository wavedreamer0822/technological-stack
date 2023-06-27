#pragma once
#include "HeadBase.h"
#include "FlowTypes.h"
#include "MaterialData.h"
#include "MaterialLib.h"
#include "Value1Const.h"
#include "SIMPLEMethods.h"
#include "ConvectionSchemes.h"
namespace LxCFD
{
   class PhysicalModel : public HeadBase
   {
   public:
      PhysicalTypes PhysicalType;
      void SetPhysicalType(PhysicalTypes physicalType)
      {
         PhysicalType = physicalType;
         if (MaterialData == nullptr || MaterialData->PhysicalType != physicalType)
         {
            MaterialLib mlib;
            MaterialData = mlib.GetDefaultMaterial(physicalType);
         }
      }
      std::unique_ptr<MaterialData> MaterialData;

      FlowTypes FlowType;
      SIMPLEMethods SIMPLEMethod = SIMPLEMethods::SIMPLE;
      ConvectionSchemes ConvectionScheme = ConvectionSchemes::SecondOrderUpwind;
      std::unique_ptr<Value1Base<Vector3d>> InitialVelocity = std::unique_ptr<Value1Const::Vector>(new Value1Const::Vector(Vector3d()));

      bool IsGravityEnabled = false;
      Vector3d Gravity = Vector3d(0, 0, -9.8);

      bool IsEnergyEnabled = false;
      double EnergyRelaxFactor = 1;
      std::unique_ptr<Value1Base<double>> InitialTemperature = std::unique_ptr<Value1Base<double>>(new Value1Const::Double(300));

      //RaditionTypes ? RaditionType;

      double MinWallDistanceLimit = 1e-6;
      bool IsBoussinesqEnabled = false;
      double ReferenceTemperature = 300;
   };
}