#include "SumMonitor.h"

namespace LxCFD
{
    void SumMonitor::CalCellValue(FvZone &selectedZone, std::vector<double> &scalarArray, int taskIndex)
    {
        double sum = 0;
        int i1, endp1;
        selectedZone.InnerIndex.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            sum += scalarArray.at(i1);
        }
        ThreadsMath::AddToSum(sum);
    }

    void SumMonitor::CalFaceValue(FvZone &selectedZone, FvThread &selectedThread, std::vector<double> &scalarArray, int taskIndex)
    {
        double sum = 0;
        int i1, endp1;
        selectedThread.ThreadIndex.CellIDs.GetSeg(i1, endp1, taskIndex);
        for (; i1 < endp1; ++i1)
        {
            sum += scalarArray.at(i1);
        }
        ThreadsMath::AddToSum(sum);
    }
}