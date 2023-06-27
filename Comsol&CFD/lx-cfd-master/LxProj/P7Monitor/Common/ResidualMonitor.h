#pragma once
#include "MonitorBase.h"
#include "ICalResidual.h"

namespace LxCFD
{
    class ResidualMonitor : public MonitorBase
    {
    public:
        ResidualMonitor(const std::string & name);
        std::vector<ICalResidual *> Residuals;
        virtual void Reset(ResetTypes clearType) override;
        virtual void RunMonitor() override;
    };
}