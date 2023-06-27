#include "ResidualMonitor.h"

namespace LxCFD
{
    ResidualMonitor::ResidualMonitor(const std::string &name)
    {
        Name = name;
    }
    void ResidualMonitor::Reset(ResetTypes clearType)
    {
        MonitorBase::Reset(clearType);
        switch (clearType)
        {
        case ResetTypes::ClearToLoadSimulation:
        case ResetTypes::ClearToLoadMesh:
        case ResetTypes::ClearFields:
        case ResetTypes::UpdateSolveCenter:
            Residuals.clear();
            break;
        case ResetTypes::None:
        default:
            break;
        }
    }

    void ResidualMonitor::RunMonitor()
    {
        if (Residuals.size() > 0)
        {
            double normalRc = 0;
            for (auto &s : Residuals)
            {
                double Rc, acPhic;
                s->GetResidual_Reset(Rc, acPhic);
                if (acPhic == 0)
                    continue;
                double local = Rc / acPhic;
                if (local > normalRc)
                {
                    normalRc = local;
                }
            }
            CurrentResult = normalRc;
            IsCurrentExist = true;
        }
        else
        {
            IsCurrentExist = false;
            CurrentResult = 0;
        }
    }
}