#pragma once
#include "UserMonitorBase.h"
namespace LxCFD
{
    class SumMonitorBase : public UserMonitorBase
    {
    public:
        virtual void RunMonitor() override;
    };
}