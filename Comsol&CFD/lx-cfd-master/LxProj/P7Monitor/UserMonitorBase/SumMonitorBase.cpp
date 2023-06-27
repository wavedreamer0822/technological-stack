#include "SumMonitorBase.h"

namespace LxCFD
{
    void SumMonitorBase::RunMonitor()
    {
        IsCurrentExist = false;
        RunStatistic();
        double sum1, sum2, sum3;
        ThreadsMath::GetSum(sum1, sum2, sum3);
        CurrentResult = sum1;
    }
}