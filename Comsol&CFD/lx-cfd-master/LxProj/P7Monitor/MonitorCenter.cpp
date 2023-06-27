#include "MonitorCenter.h"
#include "AppRes.h"
namespace LxCFD
{
    MonitorCenter::MonitorCenter()
    {
        ResidualMonitors.reserve(10);
        ResidualMonitors.push_back(&Continuity);
        ResidualMonitors.push_back(&Vel_U);
        ResidualMonitors.push_back(&Vel_V);
        ResidualMonitors.push_back(&Vel_W);
        ResidualMonitors.push_back(&Temperature);
        ResidualMonitors.push_back(&Turb_k);
        ResidualMonitors.push_back(&Turb_omega);
    }
    void MonitorCenter::Reset(ResetTypes clearType)
    {
        for (auto &s : ResidualMonitors)
        {
            s->Reset(clearType);
        }
        for (auto &s : UserMonitors)
        {
            s->Reset(clearType);
        }
    }
    void MonitorCenter::Monitor_Steady()
    {
        std::stringstream ss;
        ss.precision(7);
        ss << "step:" << AppRes::StepsCenter->SteadyStep.StepsCount << "   ";
        for (auto &s : ResidualMonitors)
        {
            s->RunMonitor();
            if (s->IsCurrentExist)
            {
                ss << s->Name << ":" << s->CurrentResult << "   ";
            }
        }
        LxConsole::Calc(ss.str());
        for (auto &m : UserMonitors)
        {
            if (m->IsRunAsSteadyStep)
            {
                m->RunMonitor();
            }
        }
    }
    void MonitorCenter::Monitor_Transient()
    {
        std::stringstream ss;
        ss.precision(7);
        ss << "time step:" << AppRes::StepsCenter->TransientStep.StepsCount << "   "
           << "result time:"; //<<AppRes::SolveCenter;
        LxConsole::Calc(ss.str());
        for (auto &m : UserMonitors)
        {
            if (m->IsRunAsSteadyStep)
                continue;
            m->RunMonitor();
        }
        // LxConsole::Info(string.Format($ "===time step: {AppRes.StepsCenter.TransientStep.StepsCount} result time:{AppRes.SolveCenter.TransientTime.resultTime}==="));
    }
}