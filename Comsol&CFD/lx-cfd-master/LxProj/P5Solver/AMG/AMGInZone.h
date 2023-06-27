#pragma once
#include <atomic>
#include "AMGBase.h"
#include "BiCGStabInZone.h"
#include "MGMeshCreator.h"
#include "ISolvableZone.h"
namespace LxCFD
{
    class AMGInZone : public AMGBase, public ISolvableZone, public IProvideVariableCount
    {
    public:
        std::vector<std::unique_ptr<MGZone>> MgZones;
        int MaxCoarseLevel = -1;
        std::vector<int> *e_FixValue;
        std::vector<int> *e_ALUO0;
        std::vector<int> *e_Couple;
        std::atomic<double> Max_acPhic = 0;
        std::atomic<double> Max_Rc = 0;
        BiCGStabInZone *BiCGSolver;

        void Create(MGMeshCreator &commonData, IProvideZoneTopology *startZone, int startZoneCellLength, std::vector<double> *zoneCellCommonArray);
        void LinkToMatrix(IAMGSolvableZone *matrix);
        void Restrict(int taskIndex);
        void Prolong(int taskIndex);
        virtual int GetVariableCount() override;
        virtual void CalResidual(int taskIndex) override;
        virtual void GetResidual_Reset(double &out_maxRc, double &out_maxacPhic) override;
        virtual void CalByJacobi_Step1(int taskIndex) override;
        virtual void CalByJacobi_Step2(int taskIndex) override;
        virtual void Cal_pArray(int taskIndex) override;
        virtual void Cal_rArray(int taskIndex) override;
        virtual void Cal_rhoPart1(int taskIndex) override;
        virtual void Cal_sArray(int taskIndex) override;
        virtual void Cal_tArray_omega1(int taskIndex) override;
        virtual void Cal_vArray_alpha1(int taskIndex) override;
        virtual void Cal_xArray(int taskIndex) override;
        virtual void Cal_yArray(int taskIndex) override;
        virtual void Cal_zArray(int taskIndex) override;
        virtual void Initialize_Step1_r0rp1rho(int taskIndex) override;
    };
}