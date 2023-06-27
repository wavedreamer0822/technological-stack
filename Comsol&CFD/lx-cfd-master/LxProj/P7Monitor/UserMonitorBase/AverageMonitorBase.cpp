#include "AverageMonitorBase.h"

namespace LxCFD
{
    void AverageMonitorBase::RunMonitor()
    {
        IsCurrentExist = false;
        RunStatistic();
        double sum1, sum2, sum3;
        ThreadsMath::GetSum(sum1, sum2, sum3);
        CurrentResult = sum1 / sum2;
    }
}