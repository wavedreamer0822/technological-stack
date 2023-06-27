#pragma once
#include "UserMonitorBase.h"

namespace LxCFD
{
    class MinMonitor : public UserMonitorBase
    {
    public:
        virtual void RunMonitor() override;
        virtual void CalCellValue(FvZone &selectedZone, std::vector<double> &scalarArray, int taskIndex) override;
        virtual void CalFaceValue(FvZone &selectedZone, FvThread &selectedThread, std::vector<double> &scalarArray, int taskIndex) override;
    };
}