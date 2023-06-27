#pragma once
#include "PressureCorrectionBasic.h"
namespace LxCFD
{
    class PressureCorrection : public PressureCorrectionBasic
    {
    public:
        std::shared_ptr<std::vector<PhysicalFaceOverRelax>> PhyFaces;

        virtual void CheckCreate(FvZone &zone) override;
        virtual void Setb_Step1_Cor(int taskIndex) override;
        virtual void Setb_Step2_Cor(int taskIndex) override;

    protected:
        virtual void set_ALU_inner(int taskIndex) override;
        virtual void set_ALU_bound(IndexNumber &indexNumber, int taskIndex) override;
        void set_b_bound(IndexNumber &indexNumber, int taskIndex);
        virtual void addPressureCorrectionToMassFlux_inner(IndexNumber &indexNumber, int taskIndex) override;
        virtual void addPressureCorrectionToMassFlux_bound(IndexNumber &indexNumber, int taskIndex) override;
    };
}