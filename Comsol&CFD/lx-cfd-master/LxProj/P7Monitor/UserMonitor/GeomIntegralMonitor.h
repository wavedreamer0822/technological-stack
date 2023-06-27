#pragma once
#include "SumMonitorBase.h"

namespace LxCFD
{
    class GeomIntegralMonitor : public SumMonitorBase
    {
    public:
        virtual void CalCellValue(FvZone &selectedZone, std::vector<double> &scalarArray, int taskIndex) override;
        virtual void CalFaceValue(FvZone &selectedZone, FvThread &selectedThread, std::vector<double> &scalarArray, int taskIndex) override;
    };
}