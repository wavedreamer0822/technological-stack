#include "MatrixADbBase.h"

namespace LxCFD
{

    void MatrixADbBase::CheckCreate(FvZone &zone)
    {
        ScalarBase::CheckCreate(zone);
        LxTool::CheckCreateVector(ADiag, Cells->size());
        LxTool::CheckCreateVector(b, Cells->size());
    }
    void MatrixADbBase::Relax(int taskIndex)
    {
        if (RelaxFactor == 1)
            return;
        relax(*InnerIndex, taskIndex);
    }

    void MatrixADbBase::clear_eFlags()
    {
        e_FixValue.clear();
        e_ALUO0.clear();
        e_Couple.clear();
    }
    void MatrixADbBase::relax(IndexNumber &indexNumber, int taskIndex)
    {
        double relax1 = (1 - RelaxFactor);
        double relaxFactorReverse = 1 / RelaxFactor;
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            double &adiag = ADiag->at(i1);
            adiag *= relaxFactorReverse;
            b->at(i1) += relax1 * adiag * x->at(i1);
        }
    }
    void MatrixADbBase::relax_bPart(IndexNumber &indexNumber, int taskIndex) //当A不变时，relax不需要重复求A，仅求b减少计算量
    {
        double relax1 = (1 - RelaxFactor);
        int i1, endp1;
        indexNumber.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            b->at(i1) += relax1 * ADiag->at(i1) * x->at(i1);
        }
    }
}