#include "MGZone.h"
#include "AMGInZone.h"
#include "ThreadsMath.h"
namespace LxCFD
{
    ShortArray::Shallow &MGZone::GetCellOFaces(int cellID)
    {
        return Cells.at(cellID).OFaces;
    }

    ShortArray::Shallow &MGZone::GetCellNFaces(int cellID)
    {
        return Cells.at(cellID).NFaces;
    }

    int MGZone::GetFaceOSideCell(int faceID)
    {
        return Faces.at(faceID).OSideCell;
    }

    int MGZone::GetFaceNSideCell(int faceID)
    {
        return Faces.at(faceID).NSideCell;
    }

    ONPair MGZone::GetONCellID(int faceID)
    {
        return Faces.at(faceID).GetONCellID();
    }

    IndexNumber &MGZone::GetInnerIndex()
    {
        return InnerIndex;
    }
    IndexNumber &MGZone::GetTotalIndex()
    {
        return TotalIndex;
    }
    int MGZone::GetThreadCount()
    {
        return ThreadIndexs.size();
    }

    IndexNumber &MGZone::GetThreadIndex(int threadID)
    {
        return ThreadIndexs.at(threadID);
    }
    void MGZone::CreateArray(AMGInZone *inAMGSolver, std::vector<double> *eCommon)
    {
        e.resize(Cells.size());
        ADiag.resize(Cells.size());
        ALUO.resize(Faces.size());
        ALUN.resize(InnerIndex.FaceIDs.GetCount());
        e_Common = eCommon;
        InAMGSolver = inAMGSolver;
    }

    void MGZone::SetFinerZone(IAMGSolvableZone *fineZone)
    {
        FinerZone = fineZone;
        e_FinerZone = FinerZone->GetProlongArray();
    }
    void MGZone::Restrict_ArLUe(int taskIndex)
    {
        int i1, endp1;
        InnerIndex.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            double &adiag = ADiag.at(i1);
            MGCell &cell = Cells.at(i1);
            FinerZone->Restrict_Ar(adiag, cell);
            e.at(i1) = cell.r / adiag;
        }
        //A_LU
        InnerIndex.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FinerZone->Restrict_ALU(ALUO.at(i1), ALUN.at(i1), Faces.at(i1));
        }
        for (auto &b : *InAMGSolver->e_FixValue)
        {
            set_ALUO(ThreadIndexs.at(b), 0, taskIndex); //理论上ALU不是0，e是0，这里直接设置ALU是0,不再初始化e
        }
        for (auto &b : *InAMGSolver->e_ALUO0)
        {
            set_ALUO(ThreadIndexs.at(b), 0, taskIndex);
        }
        for (auto &b : *InAMGSolver->e_Couple)
        {
            set_ALUO(ThreadIndexs.at(b), 1, taskIndex);
        }
    }
    void MGZone::Restrict_re(int taskIndex)
    {
        int i1, endp1;
        InnerIndex.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            MGCell &cell = Cells.at(i1);
            FinerZone->Restrict_r(cell);
            e.at(i1) = cell.r / ADiag.at(i1);
        }
    }
    void MGZone::Prolong(int taskIndex)
    {
        int i1, endp1;
        InnerIndex.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            double e = this->e.at(i1);
            for (auto &finecell : Cells.at(i1).FineCells)
            {
                e_FinerZone->at(finecell) += e;
            }
        }
    }

    void MGZone::set_ALUO(IndexNumber &indexNumber, double TargetValue, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            ALUO.at(i1) = TargetValue;
        }
    }
    double MGZone::cal_rMinusALU(MGCell &coarseCell, std::vector<double> &fromArray)
    {
        double rMinus = coarseCell.r;
        for (auto &ofid : coarseCell.OFaces)
        {
            rMinus -= ALUO.at(ofid) * fromArray.at(Faces.at(ofid).NSideCell);
        }
        for (auto &nfid : coarseCell.NFaces)
        {
            rMinus -= ALUN.at(nfid) * fromArray.at(Faces.at(nfid).OSideCell);
        }
        return rMinus;
    }

    double MGZone::calALUProductValue(MGCell &coarseCell, std::vector<double> &fromArray)
    {
        double aluprotuct = 0;
        for (auto &ofid : coarseCell.OFaces)
        {
            aluprotuct += ALUO.at(ofid) * fromArray.at(Faces.at(ofid).NSideCell);
        }
        for (auto &nfid : coarseCell.NFaces)
        {
            aluprotuct += ALUN.at(nfid) * fromArray.at(Faces.at(nfid).OSideCell);
        }
        return aluprotuct;
    }
    void MGZone::CalByJacobi_Step1(int taskIndex)
    {
        cal_x(InnerIndex, e, *e_Common, taskIndex);
    }
    void MGZone::CalByJacobi_Step2(int taskIndex)
    {
        cal_x(InnerIndex, *e_Common, e, taskIndex);
    }

    void MGZone::cal_x(IndexNumber &indexNumber, std::vector<double> &fromArray, std::vector<double> &toArray, int taskIndex)
    {
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            toArray.at(i1) = cal_rMinusALU(Cells.at(i1), fromArray) / ADiag.at(i1);
        }
    }
    void MGZone::Restrict_Ar(double &out_A, MGCell &mgCell)
    {
        double r = 0;
        double atemp = 0;
        for (auto &cell : mgCell.FineCells)
        {
            double adiag = ADiag.at(cell);
            atemp += adiag;
            r += cal_rMinusALU(Cells.at(cell), e) - adiag * e.at(cell);
        }
        for (auto &face : mgCell.InnerFineFaces)
        {
            atemp += ALUO.at(face) + ALUN.at(face);
        }
        out_A = atemp;
        mgCell.r = r;
    }
    void MGZone::Restrict_r(MGCell &mgCell)
    {
        double r = 0;
        for (auto &cell : mgCell.FineCells)
        {
            r += cal_rMinusALU(Cells.at(cell), e) - ADiag.at(cell) * e.at(cell);
        }
        mgCell.r = r;
    }
    void MGZone::Restrict_ALU(double &out_ALUO, double &out_ALUN, MGFace &mgFace)
    {
        double aluo = 0, alun = 0;
        for (auto &fineface : mgFace.FineFaces_O2N)
        {
            aluo += ALUO.at(fineface);
            alun += ALUN.at(fineface);
        }
        for (auto &fineface : mgFace.FineFaces_N2O)
        {
            aluo += ALUN.at(fineface);
            alun += ALUO.at(fineface);
        }
        out_ALUO = aluo;
        out_ALUN = alun;
    }
    std::vector<double> *MGZone::GetProlongArray()
    {
        return &e;
    }
    void MGZone::GetBounds(std::vector<int> *&out_e_FixValue, std::vector<int> *&out_e_ALUO0, std::vector<int> *&out_e_Couple)
    {
        throw std::domain_error("此处不需要实现该功能");
    }
    void MGZone::Initialize_Step1_r0rp1rho(int taskIndex)
    {
        std::vector<double> &r0 = *InAMGSolver->BiCGSolver->r0;
        std::vector<double> &r = *InAMGSolver->BiCGSolver->r;
        std::vector<double> &p = InAMGSolver->BiCGSolver->p;
        int i1, endp1;
        InnerIndex.CellIDs.GetSeg(i1, endp1, taskIndex);
        double temp = 0;
        for (; i1 < endp1; ++i1)
        {
            double Rc = r.at(i1) = r0.at(i1) = p.at(i1) = cal_rMinusALU(Cells.at(i1), e) - ADiag.at(i1) * e.at(i1);
            temp += Rc * Rc;
        }
        ThreadsMath::AddToSum(temp);
    }
    void MGZone::Cal_rhoPart1(int taskIndex)
    {
        InAMGSolver->BiCGSolver->Cal_r_Dot_r0(InnerIndex, taskIndex);
    }
    void MGZone::Cal_pArray(int taskIndex)
    {
        InAMGSolver->BiCGSolver->Cal_pArray(InnerIndex, taskIndex);
    }
    void MGZone::Cal_yArray(int taskIndex)
    {
        InAMGSolver->BiCGSolver->Cal_yArray(InnerIndex, ADiag, taskIndex);
    }
    void MGZone::Cal_vArray_alpha1(int taskIndex)
    {
        std::vector<double> &v = InAMGSolver->BiCGSolver->v;
        std::vector<double> &y = InAMGSolver->BiCGSolver->y;
        std::vector<double> &r0 = *InAMGSolver->BiCGSolver->r0;
        int i1, endp1;
        InnerIndex.CellIDs.GetSeg(i1, endp1, taskIndex);
        double temp = 0;
        for (; i1 < endp1; ++i1)
        {
            double vt = v.at(i1) = ADiag.at(i1) * y.at(i1) + calALUProductValue(Cells.at(i1), y);
            temp += r0[i1] * vt;
        }
        ThreadsMath::AddToSum(temp);
    }
    void MGZone::Cal_sArray(int taskIndex)
    {
        InAMGSolver->BiCGSolver->Cal_sArray(InnerIndex, taskIndex);
    }
    void MGZone::Cal_zArray(int taskIndex)
    {
        InAMGSolver->BiCGSolver->Cal_zArray(InnerIndex, ADiag, taskIndex);
    }
    void MGZone::Cal_tArray_omega1(int taskIndex)
    {
        std::vector<double> &s = *InAMGSolver->BiCGSolver->r;
        std::vector<double> &z = InAMGSolver->BiCGSolver->z;
        std::vector<double> &t = InAMGSolver->BiCGSolver->t;
        int i1, endp1;
        InnerIndex.CellIDs.GetSeg(i1, endp1, taskIndex);
        double temp1 = 0, temp2 = 0;
        for (; i1 < endp1; ++i1)
        {
            double st = s.at(i1);
            double tt = t.at(i1) = ADiag.at(i1) * z.at(i1) + calALUProductValue(Cells.at(i1), z);
            temp1 += tt * st;
            temp2 += tt * tt;
        }
        ThreadsMath::AddToSum(temp1, temp2);
    }
    void MGZone::Cal_xArray(int taskIndex)
    {
        InAMGSolver->BiCGSolver->Cal_xArray(InnerIndex, e, taskIndex);
    }
    void MGZone::Cal_rArray(int taskIndex)
    {
        InAMGSolver->BiCGSolver->Cal_rArray(InnerIndex, taskIndex);
    }

    void MGZone::CalResidual(int taskIndex)
    {
        int i1, endp1;
        InnerIndex.CellIDs.GetSeg(i1, endp1, taskIndex);
        double max_acphic = 0, max_Rc = 0;
        for (; i1 < endp1; ++i1)
        {
            double acphic = ADiag.at(i1) * e.at(i1);
            double Rc = cal_rMinusALU(Cells.at(i1), e) - acphic;
            acphic = std::fabs(acphic + Rc); //防止一开始acphic为0
            Rc = fabs(Rc);
            if (acphic > max_acphic)
                max_acphic = acphic;
            if (Rc > max_Rc)
                max_Rc = Rc;
        }
        ThreadsMath::KeepMax(InAMGSolver->Max_Rc, max_Rc);
        ThreadsMath::KeepMax(InAMGSolver->Max_acPhic, max_acphic);
    }
    void MGZone::GetResidual_Reset(double &out_maxRc, double &out_maxacPhic)
    {
        throw std::domain_error("此处不需要实现该功能");
    }
}