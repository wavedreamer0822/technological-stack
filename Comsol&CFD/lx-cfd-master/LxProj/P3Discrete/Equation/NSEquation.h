#pragma once
#include "NSEquationBase.h"
#include "BoundaryHeadBase.h"
#include "ConvectionSchemes.h"
#include "MassFluxBase.h"
#include "FvThread.h"
namespace LxCFD
{
   class NSEquation : public NSEquationBase
   {
   public:
      class BoundaryFixValueWall : public BoundaryHeadBase
      {
      public:
         std::shared_ptr<Value1Base<double>> FixValue;
         ValueStateLog SetxState;
         void SetFixValue(std::shared_ptr<Value1Base<double>> fixValue);
      };
      class BoundaryScalarSymmetry : public BoundaryHeadBase
      {
      };
      class BoundaryFlowValue : public BoundaryHeadBase
      {
      public:
         std::shared_ptr<Value1Base<double>> BaseValue;
         void SetParameter(std::shared_ptr<Value1Base<double>> baseValue);
      };
      class BoundaryFixFlux : public BoundaryHeadBase
      {
      public:
         std::shared_ptr<Value1Base<double>> Flux;
         void SetParameter(std::shared_ptr<Value1Base<double>> flux);
      };
      std::vector<std::unique_ptr<BoundaryFixValueWall>> FixValueWallBounds;
      std::vector<std::unique_ptr<BoundaryScalarSymmetry>> SymmetryBounds;
      std::vector<std::unique_ptr<BoundaryFlowValue>> FlowValueBounds;
      std::vector<std::unique_ptr<BoundaryFixFlux>> FluxBounds;
      std::vector<std::unique_ptr<BoundaryHeadBase>> CoupledWalls;
      ConvectionSchemes ConvectionScheme;
      void SetZone_CommonTerm(std::shared_ptr<Value1Base<double>> gamma, std::shared_ptr<ValueBase<double>> source, std::shared_ptr<Value1Base<double>> iniValue, double relaxFactor);
      void SetZone_ConvTerm(std::shared_ptr<Value1Base<double>> conv, ConvectionSchemes convectionScheme, MassFluxBase &massBase);
      void SetBoundary_fixValue(std::shared_ptr<Value1Base<double>> fixValue, FvThread &thread);
      void SetBoundary_symmetry(FvThread &thread);
      void SetBoundary_flow(std::shared_ptr<Value1Base<double>> baseValue, FvThread &thread);
      void SetBoundary_Coupled_Wall(FvThread &thread);
      virtual void Initialize() override;
      virtual void Set_x_Bound(int taskIndex) override;
      virtual void SetAb_Step1(int taskIndex) override;
      virtual void SetAb_Step2(int taskIndex) override;
      virtual void Update_x_Bound(int taskIndex) override;
      void initialize(int taskIndex);
   };
}