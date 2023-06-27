#include "MatrixBase.h"
#include "FvZone.h"
namespace LxCFD
{
    void MatrixBase::CheckCreate(FvZone &zone)
    {
        MatrixADbBase::CheckCreate(zone);
        LxTool::CheckCreateVector(ALUO, Faces->size());
        LxTool::CheckCreateVector(ALUN, Faces->size());
    }
    void MatrixBase::set_ALU_0(IndexNumber &indexNumber, int taskIndex)
    {
        int i1, endp1;
        indexNumber.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            ALUO->at(i1) = ALUN->at(i1) = 0;
        }
    }
    double MatrixBase::calALUProductValue(FvCell &cell, std::vector<double> &fromArray)
    {
        double aluProductValue = 0;
        for (auto &ofid : cell.OFaces)
        {
            aluProductValue += ALUO->at(ofid) * fromArray.at(Faces->at(ofid).NSideCell);
        }
        for (auto &nfid : cell.NFaces)
        {
            aluProductValue += ALUN->at(nfid) * fromArray.at(Faces->at(nfid).OSideCell);
        }
        return aluProductValue;
    }

    void MatrixBase::cal_x(IndexNumber &indexNumber, std::vector<double> &fromArray, std::vector<double> &toArray, int taskIndex)
    {
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            toArray.at(i1) = (b->at(i1) - calALUProductValue(Cells->at(i1), fromArray)) / ADiag->at(i1);
        }
    }
    void MatrixBase::cal_x_Copy(IndexNumber &indexNumber, std::vector<double> &fromArray, std::vector<double> &toArray, int taskIndex)
    {
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            toArray.at(i1) = fromArray.at(i1);
        }
    }

    void MatrixBase::CalResidual(int taskIndex)
    {
        int i1, endp1;
        InnerIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        double max_acphic = 0, max_Rc = 0;
        for (; i1 < endp1; ++i1)
        {
            double acphic = ADiag->at(i1) * x->at(i1);
            double Rc = std::fabs(acphic + calALUProductValue(Cells->at(i1), *x) - b->at(i1));
            acphic = std::fabs(acphic);
            if (acphic > max_acphic)
                max_acphic = acphic;
            if (Rc > max_Rc)
                max_Rc = Rc;
        }
        ThreadsMath::KeepMax(Max_Rc, max_Rc);
        ThreadsMath::KeepMax(Max_acPhic, max_acphic);
    }
    void MatrixBase::GetResidual_Reset(double &out_Rc, double &out_acPhic)
    {
        out_Rc = Max_Rc;
        out_acPhic = Max_acPhic;
        Max_Rc = 0;
        Max_acPhic = 0;
    }

    void MatrixBase::CalByJacobi_Step1(int taskIndex)
    {
        for (auto &b : e_FixValue)
        {
            cal_x_Copy(Zone->GetThreadIndex(b), *x, *x_Common, taskIndex);
        }
        cal_x(*InnerIndex, *x, *x_Common, taskIndex);
    }

    void MatrixBase::CalByJacobi_Step2(int taskIndex)
    {
        cal_x(*InnerIndex, *x_Common, *x, taskIndex);
    }

    void MatrixBase::CalByExplicit_Step1(int taskIndex)
    {
        cal_x(*InnerIndex, *x, *x_Common, taskIndex);
    }

    void MatrixBase::CalByExplicit_Step2(int taskIndex)
    {
        cal_x_Copy(*InnerIndex, *x_Common, *x, taskIndex);
    }
    void MatrixBase::Initialize_Step1_r0rp1rho(int taskIndex)
    {
        auto &r0 = *Zone->BiCGSolver.r0;
        auto &r = *Zone->BiCGSolver.r;
        auto &p = Zone->BiCGSolver.p;
        int i1, endp1;
        InnerIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        double temp = 0;
        for (; i1 < endp1; ++i1)
        {
            double rt = r.at(i1) = r0.at(i1) = p.at(i1) = b->at(i1) - calALUProductValue(Cells->at(i1), *x) - ADiag->at(i1) * x->at(i1);
            temp += rt * rt;
        }
        ThreadsMath::AddToSum(temp);
        for (int &b : e_FixValue)
        {
            Zone->BiCGSolver.Initialize0ValueInArray(Zone->GetThreadIndex(b), taskIndex);
        }
    }
    void MatrixBase::Cal_rhoPart1(int taskIndex)
    {
        Zone->BiCGSolver.Cal_r_Dot_r0(*InnerIndex, taskIndex);
    }
    void MatrixBase::Cal_pArray(int taskIndex)
    {
        Zone->BiCGSolver.Cal_pArray(*InnerIndex, taskIndex);
    }
    void MatrixBase::Cal_yArray(int taskIndex)
    {
        Zone->BiCGSolver.Cal_yArray(*InnerIndex, *ADiag, taskIndex);
    }
    void MatrixBase::Cal_vArray_alpha1(int taskIndex)
    {
        auto &v = Zone->BiCGSolver.v;
        auto &y = Zone->BiCGSolver.y;
        auto &r0 = *Zone->BiCGSolver.r0;
        int i1, endp1;
        InnerIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        double temp = 0;
        for (; i1 < endp1; ++i1)
        {
            double vt = v.at(i1) = ADiag->at(i1) * y.at(i1) + calALUProductValue(Cells->at(i1), y);
            temp += r0[i1] * vt;
        }
        ThreadsMath::AddToSum(temp);
    }
    void MatrixBase::Cal_sArray(int taskIndex)
    {
        Zone->BiCGSolver.Cal_sArray(*InnerIndex, taskIndex);
    }
    void MatrixBase::Cal_zArray(int taskIndex)
    {
        Zone->BiCGSolver.Cal_zArray(*InnerIndex, *ADiag, taskIndex);
    }
    void MatrixBase::Cal_tArray_omega1(int taskIndex)
    {
        auto &s = *Zone->BiCGSolver.r;
        auto &z = Zone->BiCGSolver.z;
        auto &t = Zone->BiCGSolver.t;
        int i1, endp1;
        InnerIndex->CellIDs.GetSeg(i1, endp1, taskIndex);
        double temp1 = 0, temp2 = 0;
        for (; i1 < endp1; ++i1)
        {
            double st = s.at(i1);
            double tt = t.at(i1) = ADiag->at(i1) * z.at(i1) + calALUProductValue(Cells->at(i1), z);
            temp1 += tt * st;
            temp2 += tt * tt;
        }
        ThreadsMath::AddToSum(temp1, temp2);
    }
    void MatrixBase::Cal_xArray(int taskIndex)
    {
        Zone->BiCGSolver.Cal_xArray(*InnerIndex, *x, taskIndex);
    }
    void MatrixBase::Cal_rArray(int taskIndex)
    {
        Zone->BiCGSolver.Cal_rArray(*InnerIndex, taskIndex);
    }
    void MatrixBase::Restrict_Ar(double &out_A, MGCell &mgCell)
    {
        double Atemp = 0;
        double rtemp = 0;
        for (auto &finecell : mgCell.FineCells)
        {
            double atemp = ADiag->at(finecell);
            Atemp += atemp;
            rtemp += b->at(finecell) - calALUProductValue(Cells->at(finecell), *x) - atemp * x->at(finecell);
        }
        for (auto &innerfineface : mgCell.InnerFineFaces)
        {
            Atemp += ALUO->at(innerfineface) + ALUN->at(innerfineface);
        }
        out_A = Atemp;
        mgCell.r = rtemp;
    }
    void MatrixBase::Restrict_r(MGCell &mgCell)
    {
        double rtemp = 0;
        for (auto &finecell : mgCell.FineCells)
        {
            rtemp += b->at(finecell) - calALUProductValue(Cells->at(finecell), *x) - ADiag->at(finecell) * x->at(finecell);
        }
        mgCell.r = rtemp;
    }
    void MatrixBase::Restrict_ALU(double &out_ALUO, double &out_ALUN, MGFace &mgFace)
    {
        double O2N = 0;
        double N2O = 0;
        for (int &fineface : mgFace.FineFaces_O2N)
        {
            O2N += ALUO->at(fineface);
            N2O += ALUN->at(fineface);
        }
        for (int &fineface : mgFace.FineFaces_N2O)
        {
            O2N += ALUN->at(fineface);
            N2O += ALUO->at(fineface);
        }
        out_ALUO = O2N;
        out_ALUN = N2O;
    }

    std::vector<double> *MatrixBase::GetProlongArray()
    {
        return x.get();
    }
    void MatrixBase::GetBounds(std::vector<int> *&out_e_FixValue, std::vector<int> *&out_e_ALUO0, std::vector<int> *&out_e_Couple)
    {
        out_e_FixValue = &e_FixValue;
        out_e_ALUO0 = &e_ALUO0;
        out_e_Couple = &e_Couple;
    }
}