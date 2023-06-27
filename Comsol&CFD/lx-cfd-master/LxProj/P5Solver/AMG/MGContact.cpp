#include "MGContact.h"
#include "AMGInContact.h"

namespace LxCFD
{
    ShortArray::Shallow &MGContact::GetOZoneCellOFaces(int cellIndex)
    {
        return O_Cells->at(cellIndex).OFaces;
    }
    ShortArray::Shallow &MGContact::GetNZoneCellOFaces(int cellIndex)
    {
        return N_Cells->at(cellIndex).OFaces;
    }
    IndexNumber &MGContact::GetInnerIndex()
    {
        return InnerIndex;
    }
    void MGContact::SetArray(AMGInContact *inAMGSolver)
    {
        InAMGSolver = inAMGSolver;
        O_e = &O_Zone->e;
        O_eCommon = O_Zone->e_Common;
        N_e = &N_Zone->e;
        N_eCommon = N_Zone->e_Common;
        ALUO.resize(Pairs.size());
        ALUN.resize(Pairs.size());
    }
    void MGContact::SetFineContact(IAMGSolvableContact *finecontact)
    {
        FinerContact = finecontact;
    }
    void MGContact::Restrict_ALU(int taskIndex)
    {
        int i1, endp1;
        InnerIndex.FaceIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            FinerContact->Restrict_ALU(ALUO.at(i1), ALUN.at(i1), Pairs.at(i1));
        }
    }
    void MGContact::Restrict_ALU(double &out_ALUO, double &out_ALUN, MGPair &mgPair)
    {
        double aluo = 0, alun = 0;
        for (auto &pid : mgPair.FinePairs)
        {
            aluo += ALUO.at(pid);
            alun += ALUN.at(pid);
        }
        out_ALUO = aluo;
        out_ALUN = alun;
    }
    void MGContact::Copy_xArray(int taskIndex)
    {
        copyContact(*O_e, *N_e, taskIndex);
    }
    void MGContact::Copy_xCommonArray(int taskIndex)
    {
        copyContact(*O_eCommon, *N_eCommon, taskIndex);
    }

    void MGContact::copyContact(std::vector<double> &OArray, std::vector<double> &NArray, int taskIndex)
    {
        int i1, endp1;
        O_Index->CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            double aluproduct = 0;
            for (auto &pid : O_Cells->at(i1).OFaces)
            {
                aluproduct += ALUO.at(pid) * NArray.at(Pairs.at(pid).N_InnCell);
            }
            OArray.at(i1) = aluproduct;
        }
        N_Index->CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            double aluproduct = 0;
            for (auto &pid : N_Cells->at(i1).OFaces)
            {
                aluproduct += ALUN.at(pid) * OArray.at(Pairs.at(pid).O_InnCell);
            }
            NArray.at(i1) = aluproduct;
        }
    }
    void MGContact::Copy_yArray(int taskIndex)
    {
        copyContact(InAMGSolver->O_BiCGSolver->y, InAMGSolver->N_BiCGSolver->y, taskIndex);
    }
    void MGContact::Copy_zArray(int taskIndex)
    {
        copyContact(InAMGSolver->O_BiCGSolver->z, InAMGSolver->N_BiCGSolver->z, taskIndex);
    }
}