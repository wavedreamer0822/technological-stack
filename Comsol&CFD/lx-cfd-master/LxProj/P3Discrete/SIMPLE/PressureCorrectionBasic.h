#pragma once
#include "EquationBase.h"
#include "PressureSIMPLE.h"
#include "SIMPLEMethods.h"
#include "PhysicalFaceOverRelax.h"
namespace LxCFD
{
    class PressureCorrectionBasic : public EquationBase
    {

    public:
        SIMPLEMethods SIMPLEMethod;
        std::shared_ptr<std::vector<Vector3d>> Dc; //Dc，见591。用以求解Df,DDf。DDf见P596//Dc在保存的时候，剔除松弛的影响！
        //not local
        VelocityVector *VelocityVector;
        PressureSIMPLE *PressureSIMPLE;

        virtual void CheckCreate(FvZone &zone) override;
        void SetZone(double pressureRelaxFactor, SIMPLEMethods solvingMethod, LxCFD::VelocityVector *velocityVector, LxCFD::PressureSIMPLE *pressureInSimple, std::shared_ptr<Value1Base<double>> density);
        void SetBound_AfterSettingVelocityVector();
        virtual void Initialize() override { throw std::domain_error("Should not be called"); }
        virtual void Set_x_Bound(int taskIndex) override; //压力修正初始值都为0
        virtual void SetAb_Step1(int taskIndex) override;
        virtual void SetAb_Step2(int taskIndex) override;
        void SetAb_PCor0Point(int CellIndex);
        virtual void Relax(int taskIndex) override {}
        virtual void Update_x_Bound(int taskIndex) override;
        void ApplyPCorToUVWP(int taskIndex);
        void ApplyPCorToUVWP_NoRelax(int taskIndex);
        void CalDc_ADiagNotRelaxed(int taskIndex); //如果U V W的系数矩阵未进行过松弛//添加源项可能改动A_Diag，所以计算完A_Diag后立即计算Dc
        virtual void Setb_Step1_Cor(int taskIndex);
        virtual void Setb_Step2_Cor(int taskIndex);

    protected:
        std::vector<double> *MassFlux;
        std::vector<double> *MassImbalance;
        std::vector<double> *Pressure;
        std::shared_ptr<Value1Base<double>> Density;
        virtual void set_ALU_inner(int taskIndex);
        virtual void set_ALU_bound(IndexNumber &indexNumber, int taskIndex);
        void predict_Bound(IndexNumber &indexNumber, int taskIndex);
        void addCorrectionToUVW(IndexNumber &indexNumber, int taskIndex);
        void addCorrectionToPressure(IndexNumber &indexNumber, int taskIndex);
        void addCorrectionToPressure_NoRelax(IndexNumber &indexNumber, int taskIndex);
        virtual void addPressureCorrectionToMassFlux_inner(IndexNumber &indexNumber, int taskIndex); //需要对公式校核以下，这个公式理论上应与RhieChow一致
        virtual void addPressureCorrectionToMassFlux_bound(IndexNumber &indexNumber, int taskIndex); //需要对公式校核以下，这个公式理论上应与RhieChow一致
    };
}