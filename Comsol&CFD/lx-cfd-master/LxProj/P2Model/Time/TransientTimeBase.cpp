#include "TransientTimeBase.h"

namespace LxCFD
{
    void TransientTimeBase::SetTransientFactor()
    {
        TransientDataBase::IsSecondOrder = IsSecondOrder;
        if (IsImplicit)
        {
            GetFactor_1stOrderImplicit(TransientDataBase::Factor_Phi_1stOrder);
            GetFactor_2ndOrderImplicit(TransientDataBase::Factor_Phi_2ndOrder, TransientDataBase::Factor_PhiO_2ndOrder, TransientDataBase::Factor_PhiOO_2ndOrder);
        }
        else
        {
            GetFactor_1stOrderExplicit(TransientDataBase::Factor_Phi_1stOrder);
            GetFactor_2ndOrderExplicit(TransientDataBase::Factor_Phi_2ndOrder, TransientDataBase::Factor_PhiO_2ndOrder, TransientDataBase::Factor_PhiOO_2ndOrder);
        }
    }
    void TransientTimeBase::GetFactor_1stOrderExplicit(double &out_beforePhi)
    {
        out_beforePhi = 1.0 / dto;
    }
    void TransientTimeBase::GetFactor_2ndOrderExplicit(double &out_beforePhi, double &out_beforePhiOld, double &out_beforePhiOld2)
    {
        out_beforePhiOld2 = (dt + 2 * dto) * dto / ((dt + 2 * dto + dtoo) * (dto + dtoo));
        out_beforePhiOld = (dt + 2 * dto) * dtoo / ((dt + dto) * (dto + dtoo));
        out_beforePhi = 1 - out_beforePhiOld - out_beforePhiOld2;
        out_beforePhi = dto / (dt + dto) - out_beforePhi;
        out_beforePhiOld = dt / (dt + dto) - out_beforePhiOld;
        out_beforePhi /= dto;
        out_beforePhiOld /= dto;
        out_beforePhiOld2 /= -dto;
    }
    void TransientTimeBase::GetFactor_1stOrderImplicit(double &out_beforePhi)
    {
        out_beforePhi = 1.0 / dt;
    }
    void TransientTimeBase::GetFactor_2ndOrderImplicit(double &out_beforePhi, double &out_beforePhiOld, double &out_beforePhiOld2)
    {
        out_beforePhi = 1.0 / dt + 1.0 / (dt + dto);
        out_beforePhiOld2 = dto / (dt * (dto + dtoo));
        out_beforePhiOld = -(out_beforePhi + out_beforePhiOld2);
    }
}