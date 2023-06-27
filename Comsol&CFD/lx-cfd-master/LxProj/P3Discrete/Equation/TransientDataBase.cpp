#include "TransientDataBase.h"

namespace LxCFD
{
    bool TransientDataBase::IsSecondOrder = true;
    double TransientDataBase::Factor_Phi_1stOrder = 0;
    double TransientDataBase::Factor_Phi_2ndOrder = 0;
    double TransientDataBase::Factor_PhiO_2ndOrder = 0;
    double TransientDataBase::Factor_PhiOO_2ndOrder = 0;

    bool TransientDataBase::GetIsInitialized()
    {
        return TransientDataState != TransientDataStates::None;
    }

    void TransientDataBase::SetIsInitialized(bool isInitialized)
    {
        if (isInitialized)
        {
            TransientDataState = TransientDataStates::Only_o;
        }
        else
        {
            TransientDataState = TransientDataStates::None;
        }
    }
}