#include "MinMonitor.h"

namespace LxCFD
{
    void MinMonitor::RunMonitor()
    {
        IsCurrentExist = false;
        CurrentResult = std::numeric_limits<double>::max(); // double.MaxValue;
        RunStatistic();
    }
    void MinMonitor::CalCellValue(FvZone &selectedZone, std::vector<double> &scalarArray, int taskIndex)
    {
        double localMin = CurrentResult;
        int i1, endp1;
        selectedZone.InnerIndex.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            double &d = scalarArray.at(i1);
            if (d < localMin)
            {
                localMin = d;
            }
        }
        ThreadsMath::KeepMin(CurrentResult, localMin);
    }
    void MinMonitor::CalFaceValue(FvZone &selectedZone, FvThread &selectedThread, std::vector<double> &scalarArray, int taskIndex)
    {
        double localMin = CurrentResult;
        int i1, endp1;
        selectedThread.ThreadIndex.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            double &d = scalarArray.at(i1);
            if (d < localMin)
            {
                localMin = d;
            }
        }
        ThreadsMath::KeepMin(CurrentResult, localMin);
    }
}