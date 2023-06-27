#pragma once
#include "PossionEquationBase.h"
#include "BoundaryHeadBase.h"
#include "ValueStateLog.h"
#include "FvThread.h"
namespace LxCFD
{
    class PossionEquation : public PossionEquationBase
    {
    public:
        class BoundaryFixValue : public BoundaryHeadBase
        {
        public:
            std::shared_ptr<Value1Base<double>> FixValue = nullptr;
            ValueStateLog BoundxState;
            void SetFixValue(std::shared_ptr<Value1Base<double>> fixValue);
        };
        class BoundaryFixFlux : public BoundaryHeadBase
        {
        public:
            std::shared_ptr<Value1Base<double>> FixFlux= nullptr;
            void SetFixFlux(std::shared_ptr<Value1Base<double>> fixFlux);
        };
        class BoundaryFixhT : public BoundaryHeadBase
        {
        public:
            std::shared_ptr<Value1Base<double>> Fixh= nullptr;
            std::shared_ptr<Value1Base<double>> FixT= nullptr;
            void SetFixhT(std::shared_ptr<Value1Base<double>> fixh, std::shared_ptr<Value1Base<double>> fixT);
        };
        std::vector<std::unique_ptr<BoundaryFixValue>> FixValueBounds;
        std::vector<std::unique_ptr<BoundaryFixFlux>> FixFluxBounds;
        std::vector<std::unique_ptr<BoundaryFixhT>> FixhTBounds;
        std::vector<std::unique_ptr<BoundaryHeadBase>> CoupledBounds;

        void SetZone_CommonTerm(std::shared_ptr<Value1Base<double>> gamma, std::shared_ptr<ValueBase<double>> source, std::shared_ptr<Value1Base<double>> iniValue, double relaxFactor);
        void SetBoundary_FixValue(std::shared_ptr<Value1Base<double>> fixValue, FvThread &thread);
        void SetBoundary_FixFlux(std::shared_ptr<Value1Base<double>> fixFlux, FvThread &thread);
        void SetBoundary_FixCoupledhT(std::shared_ptr<Value1Base<double>> fixh, std::shared_ptr<Value1Base<double>> fixT, FvThread &thread);
        void SetBound_Coupled(FvThread &thread);
        virtual void Initialize() override;
        virtual void Set_x_Bound(int taskIndex) override;
        virtual void SetAb_Step1(int taskIndex) override;
        virtual void SetAb_Step2(int taskIndex) override;
        virtual void Update_x_Bound(int taskIndex) override;
    };
}