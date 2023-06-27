#pragma once
#include "MatrixADbBase.h"
#include "ISolvableZone.h"
#include "IExplicitSolvableZone.h"
#include "IAMGSolvableZone.h"
namespace LxCFD
{
    class MatrixBase : public MatrixADbBase, public ISolvableZone, public IExplicitSolvableZone, public IAMGSolvableZone
    {

    public:
        std::shared_ptr<std::vector<double>> ALUO;
        std::shared_ptr<std::vector<double>> ALUN;
        virtual void CheckCreate(FvZone &zone) override;
        virtual void CalResidual(int taskIndex) override;
        virtual void GetResidual_Reset(double &out_Rc, double &out_acPhic) override;
        virtual void CalByJacobi_Step1(int taskIndex) override;
        virtual void CalByJacobi_Step2(int taskIndex) override;
        virtual void CalByExplicit_Step1(int taskIndex) override;
        virtual void CalByExplicit_Step2(int taskIndex) override;
        virtual void Initialize_Step1_r0rp1rho(int taskIndex) override;
        virtual void Cal_rhoPart1(int taskIndex) override;
        virtual void Cal_pArray(int taskIndex) override;
        virtual void Cal_yArray(int taskIndex) override;
        virtual void Cal_vArray_alpha1(int taskIndex) override;
        virtual void Cal_sArray(int taskIndex) override;
        virtual void Cal_zArray(int taskIndex) override;
        virtual void Cal_tArray_omega1(int taskIndex) override;
        virtual void Cal_xArray(int taskIndex) override;
        virtual void Cal_rArray(int taskIndex) override;
        virtual void Restrict_Ar(double &out_A, MGCell &mgCell) override;
        virtual void Restrict_r(MGCell &mgCell) override;
        virtual void Restrict_ALU(double &out_ALUO, double &out_ALUN, MGFace &mgFace) override;
        virtual std::vector<double> *GetProlongArray() override;
        virtual void GetBounds(std::vector<int> *&out_e_FixValue, std::vector<int> *&out_e_ALUO0, std::vector<int> *&out_e_Couple) override;

    protected:
        std::atomic<double> Max_Rc = 0;
        std::atomic<double> Max_acPhic = 0;
        void set_ALU_0(IndexNumber &indexNumber, int taskIndex);
        double calALUProductValue(FvCell &cell, std::vector<double> &fromArray);
        void cal_x(IndexNumber &indexNumber, std::vector<double> &fromArray, std::vector<double> &toArray, int taskIndex);
        void cal_x_Copy(IndexNumber &indexNumber, std::vector<double> &fromArray, std::vector<double> &toArray, int taskIndex);
    };
}