#pragma once
#include "UserMonitorBase.h"

namespace LxCFD
{
    class AverageMonitorBase : public UserMonitorBase
    {
    public:
        virtual void RunMonitor() override;
    };
}