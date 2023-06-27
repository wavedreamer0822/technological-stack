#pragma once
#include <cmath>
#include <memory>
#include "MGCell.h"
#include "MGFace.h"
#include "IndexNumber.h"
#include "IProvideZoneTopology.h"
#include "IAMGSolvableZone.h"
#include "ISolvableZone.h"
namespace LxCFD
{
    class AMGInZone;
    class MGZone : public IProvideZoneTopology, public ISolvableZone, public IAMGSolvableZone
    {
    public:
        //local
        std::vector<MGCell> Cells;
        std::vector<MGFace> Faces;
        IndexNumber InnerIndex;
        IndexNumber TotalIndex;
        std::vector<IndexNumber> ThreadIndexs;
        ShortArray::Deep ShallowArrayStorage;
        virtual ShortArray::Shallow &GetCellOFaces(int cellID) override;
        virtual ShortArray::Shallow &GetCellNFaces(int cellID) override;
        virtual int GetFaceOSideCell(int faceID) override;
        virtual int GetFaceNSideCell(int faceID) override;
        virtual ONPair GetONCellID(int faceID) override;
        virtual IndexNumber &GetInnerIndex() override;
        virtual IndexNumber &GetTotalIndex() override;
        virtual int GetThreadCount() override;
        virtual IndexNumber &GetThreadIndex(int threadID) override;

    public:
        std::vector<double> e;
        std::vector<double> ADiag;
        std::vector<double> ALUO;
        std::vector<double> ALUN;
        AMGInZone *InAMGSolver;
        std::vector<double> *e_Common;
        IAMGSolvableZone *FinerZone;
        std::vector<double> *e_FinerZone;

        void CreateArray(AMGInZone *inAMGSolver, std::vector<double> *eCommon);
        void SetFinerZone(IAMGSolvableZone *fineZone);
        void Restrict_ArLUe(int taskIndex);
        void Restrict_re(int taskIndex);
        void Prolong(int taskIndex);
        void CalByJacobi_Step1(int taskIndex);
        void CalByJacobi_Step2(int taskIndex);
        virtual void Restrict_Ar(double &out_A, MGCell &mgCell) override;
        virtual void Restrict_r(MGCell &mgCell) override;
        virtual void Restrict_ALU(double &out_ALUO, double &out_ALUN, MGFace &mgFace) override;
        virtual std::vector<double> *GetProlongArray() override;
        virtual void GetBounds(std::vector<int> *&out_e_FixValue, std::vector<int> *&out_e_ALUO0, std::vector<int> *&out_e_Couple) override;
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
        virtual void CalResidual(int taskIndex) override;
        virtual void GetResidual_Reset(double &out_maxRc, double &out_maxacPhic) override;

    protected:
        void set_ALUO(IndexNumber &indexNumber, double TargetValue, int taskIndex);
        double cal_rMinusALU(MGCell &coarseCell, std::vector<double> &fromArray);
        double calALUProductValue(MGCell &coarseCell, std::vector<double> &fromArray);
        void cal_x(IndexNumber &indexNumber, std::vector<double> &fromArray, std::vector<double> &toArray, int taskIndex);
    };
}