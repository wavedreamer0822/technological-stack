#pragma once
#include "IReset.h"
#include "ResidualMonitor.h"
#include "UserMonitorBase.h"
#include <vector>
namespace LxCFD
{
    class MonitorCenter : public IReset
    {
    public:
        MonitorCenter();
        ResidualMonitor Continuity = ResidualMonitor{"连续性"};
        ResidualMonitor Vel_U = ResidualMonitor{"动量U"};
        ResidualMonitor Vel_V = ResidualMonitor{"动量V"};
        ResidualMonitor Vel_W = ResidualMonitor{"动量W"};
        ResidualMonitor Temperature = ResidualMonitor{"温度"};
        ResidualMonitor Turb_k = ResidualMonitor{"湍动能"};
        ResidualMonitor Turb_omega = ResidualMonitor{"比耗散率"};
        std::vector<ResidualMonitor *> ResidualMonitors;
        std::vector<std::unique_ptr<UserMonitorBase>> UserMonitors;
        virtual void Reset(ResetTypes clearType) override;
        void Monitor_Steady();
        void Monitor_Transient();
    };
}