#include "ConnectBase.h"
#include "FvContact.h"
namespace LxCFD
{
    void ConnectBase::CheckCreate(FvContact &contact)
    {
        ConnectHeadBase::CheckCreate(contact);
        LxTool::CheckCreateVector(ADLUb, Pairs->size());
    }
    void ConnectBase::SetArray(EquationBase &OMatrix, EquationBase &NMatrix)
    {
        O_Matrix = &OMatrix;
        O_x = OMatrix.x.get();
        O_ALUO = OMatrix.ALUO.get();
        O_ALUN = OMatrix.ALUN.get();
        O_grad = OMatrix.Grad.get();
        O_xCommon = OMatrix.x_Common;
        O_bFaceCommon = OMatrix.b_FaceCommon;

        N_Matrix = &NMatrix;
        N_x = NMatrix.x.get();
        N_ALUO = NMatrix.ALUO.get();
        N_ALUN = NMatrix.ALUN.get();
        N_grad = NMatrix.Grad.get();
        N_xCommon = NMatrix.x_Common;
        N_bFaceCommon = NMatrix.b_FaceCommon;
    }
    void ConnectBase::Copy_xCommonArray(int taskIndex)
    {
        CopyBound(*O_xCommon, *N_xCommon, taskIndex);
    }
    void ConnectBase::Copy_xArray(int taskIndex)
    {
        CopyBound(*O_x, *N_x, taskIndex);
    }
    void ConnectBase::CopyBound(std::vector<double> &OArray, std::vector<double> &NArray, int taskIndex)
    {
        int i1, endp1;
        O_Index->CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            double aluproduct = 0;
            for (auto &pid : O_Cells->at(i1).OFaces)
            {
                aluproduct += ADLUb->at(pid).a14 * NArray.at(Pairs->at(pid).N_InnCell);
            }
            OArray.at(i1) = aluproduct;
        }

        N_Index->CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            double aluproduct = 0;
            for (auto &pid : N_Cells->at(i1).OFaces)
            {
                aluproduct += ADLUb->at(pid).a41 * OArray.at(Pairs->at(pid).O_InnCell);
            }
            NArray.at(i1) = aluproduct;
        }
    }
    void ConnectBase::Copy_yArray(int taskIndex)
    {
        CopyBound(Contact->O_BiCGSolver->y, Contact->N_BiCGSolver->y, taskIndex);
    }
    void ConnectBase::Copy_zArray(int taskIndex)
    {
        CopyBound(Contact->O_BiCGSolver->z, Contact->N_BiCGSolver->z, taskIndex);
    }
    void ConnectBase::Restrict_ALU(double &out_ALUO, double &out_ALUN, MGPair &mgPair)
    {
        double aluo = 0, alun = 0;
        for (auto &fp : mgPair.FinePairs)
        {
            PairMatrix &ab = ADLUb->at(fp);
            aluo += ab.a14;
            alun += ab.a41;
        }
        out_ALUO = aluo;
        out_ALUN = alun;
    }
}