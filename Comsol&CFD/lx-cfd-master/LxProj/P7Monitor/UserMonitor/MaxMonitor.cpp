#include "MaxMonitor.h"

namespace LxCFD
{
    void MaxMonitor::RunMonitor()
    {
        IsCurrentExist = false;
        CurrentResult = std::numeric_limits<double>::min(); //   double.MinValue;
        RunStatistic();
    }
    void MaxMonitor::CalCellValue(FvZone &selectedZone, std::vector<double> &scalarArray, int taskIndex)
    {
        double localMax = CurrentResult;
        int i1, endp1;
        selectedZone.InnerIndex.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            double &d = scalarArray.at(i1);
            if (d > localMax)
            {
                localMax = d;
            }
        }
        ThreadsMath::KeepMax(CurrentResult, localMax);
    }
    void MaxMonitor::CalFaceValue(FvZone &selectedZone, FvThread &selectedThread, std::vector<double> &scalarArray, int taskIndex)
    {
        double localMax = CurrentResult;
        int i1, endp1;
        selectedThread.ThreadIndex.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            double &d = scalarArray.at(i1);
            if (d > localMax)
            {
                localMax = d;
            }
        }
        ThreadsMath::KeepMax(CurrentResult, localMax);
    }
}