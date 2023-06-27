#include "AppRes.h"

namespace LxCFD
{
    std::unique_ptr<FvMesh> AppRes::FvMesh = nullptr;
    std::unique_ptr<PhysicalCenter> AppRes::PhysicalCenter = std::unique_ptr<LxCFD::PhysicalCenter>(new LxCFD::PhysicalCenter());
    std::unique_ptr<SolveCenter> AppRes::SolveCenter = std::unique_ptr<LxCFD::SolveCenter>(new LxCFD::SolveCenter());
    std::unique_ptr<ComputeTask> AppRes::ComputeTask = std::unique_ptr<LxCFD::ComputeTask>(new LxCFD::ComputeTask());
    std::unique_ptr<StepsCenter> AppRes::StepsCenter = std::unique_ptr<LxCFD::StepsCenter>(new LxCFD::StepsCenter());
    std::unique_ptr<MonitorCenter> AppRes::MonitorCenter = std::unique_ptr<LxCFD::MonitorCenter>(new LxCFD::MonitorCenter());
    std::unique_ptr<ExcuteCenter> AppRes::ExcuteCenter = std::unique_ptr<LxCFD::ExcuteCenter>(new LxCFD::ExcuteCenter());
}