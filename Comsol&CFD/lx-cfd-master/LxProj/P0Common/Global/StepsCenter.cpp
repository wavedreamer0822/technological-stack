#include "StepsCenter.h"

namespace LxCFD
{
    void StepsCenter::StepsAndStop::ResetStopRule()
    {
        isStop_Or = false;
        isStop_And = true;
        isStop_And_isUsed = false;
    }
    void StepsCenter::StepsAndStop::AddStopRule(bool isForce, bool isStop)
    {
        if (isForce)
        {
            isStop_Or = isStop_Or || isStop;
        }
        else
        {
            isStop_And_isUsed = true;
            isStop_And = isStop_And && isStop;
        }
    }
    bool StepsCenter::StepsAndStop::IsContinue()
    {
        AddStopRule(true, StepsCount >= MaxSteps);
        if (isStop_And_isUsed)
        {
            return !(isStop_Or || isStop_And);
        }
        else
        {
            return !isStop_Or;
        }
    }
    void StepsCenter::Reset(ResetTypes resetType)
    {
        switch (resetType)
        {
        case ResetTypes::ClearToLoadSimulation:
        case ResetTypes::ClearToLoadMesh:
        case ResetTypes::ClearFields:
            SteadyStep.StepsCount = 0;
            TransientStep.StepsCount = 0;
            TotalStepCount = 0;
            break;
        case ResetTypes::UpdateSolveCenter:
        case ResetTypes::None:
        default:
            break;
        }
    }
    void StepsCenter::MoveNextStep_Steady()
    {
        SteadyStep.ResetStopRule();
        SteadyStep.StepsCount++;
        TotalStepCount++;
    }
    void StepsCenter::MoveNextStep_Transient()
    {
        TransientStep.ResetStopRule();
        TransientStep.StepsCount++;
        SteadyStep.StepsCount = 0;
    }
}