#include "TransientTimeFixed.h"
#include "AppRes.h"
namespace LxCFD
{
    void TransientTimeFixed::Initialize()
    {
        setTime();
        dt = FixInterval;
        dto = FixInterval;
        dtoo = FixInterval;
        SetTransientFactor();
    }
    void TransientTimeFixed::MoveNextTimeStep()
    {
        setTime();
    }

    std::unique_ptr<TransientTimeBase> TransientTimeFixed::GetCopy()
    {
        std::unique_ptr<TransientTimeFixed> t = std::unique_ptr<TransientTimeFixed>(new TransientTimeFixed());
        t->IsImplicit = IsImplicit;
        t->IsSecondOrder = IsSecondOrder;
        t->FixInterval = FixInterval;
        return std::move(t);
    }

    void TransientTimeFixed::setTime()
    {
        int timeStepsCount = AppRes::StepsCenter->TransientStep.StepsCount;
        if (IsImplicit)
        {
            EquationTime = FixInterval * (timeStepsCount + 1);
        }
        else
        {
            EquationTime = FixInterval * timeStepsCount;
        }
        ResultTime = FixInterval * timeStepsCount;
    }
}