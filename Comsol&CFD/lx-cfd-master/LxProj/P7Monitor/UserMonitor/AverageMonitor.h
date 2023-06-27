#pragma once
#include "AverageMonitorBase.h"

namespace LxCFD
{
    class AverageMonitor : public AverageMonitorBase
    {
    public:
        virtual void CalFaceValue(FvZone &selectedZone, FvThread &selectedThread, std::vector<double> &scalarArray, int taskIndex) override;
        virtual void CalCellValue(FvZone &selectedZone, std::vector<double> &scalarArray, int taskIndex) override;
    };
}