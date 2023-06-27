#pragma once
#include <vector>
#include <atomic>
#include "HeadBase.h"
#include "IReset.h"
#include "LxTool.h"
namespace LxCFD
{
    class MonitorBase : public HeadBase, public IReset
    {
    public:
        std::atomic<double> CurrentResult;
        bool IsCurrentExist;
        bool IsKeepData = false;
        bool IsStopRule = false;
        bool IsRunAsSteadyStep = true;

        std::vector<double> y;
        std::vector<double> x;

        virtual void RunMonitor() = 0;
        virtual void Reset(ResetTypes resetType) override;
    };
}