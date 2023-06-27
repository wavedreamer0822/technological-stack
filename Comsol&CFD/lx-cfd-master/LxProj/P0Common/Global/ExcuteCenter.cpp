#include "ExcuteCenter.h"

namespace LxCFD
{
    void ExcuteCenter::Reset(ResetTypes resetType)
    {
        switch (resetType)
        {
        case ResetTypes::ClearToLoadSimulation:
        case ResetTypes::ClearToLoadMesh:
        case ResetTypes::ClearFields:
        case ResetTypes::UpdateSolveCenter:
            //clear reset
            break;
        case ResetTypes::None:
        default:
            break;
        }
    }
    void ExcuteCenter::ExcuteBeforeStep()
    {
    }
    void ExcuteCenter::ExcuteAfterStep()
    {
    }
    void ExcuteCenter::ExcuteAfterAll()
    {
        for(auto& e : ExcuteAfterAll_Fixed)
        {
            e->Excute();
        }
    }

}