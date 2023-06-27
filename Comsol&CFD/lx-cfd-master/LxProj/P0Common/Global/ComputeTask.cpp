#include "ComputeTask.h"
#include "IReset.h"
#include "MultiThreads.h"
#include "AppRes.h"
namespace LxCFD
{
    void ComputeTask::RunForceInitialization()
    {
        _IsForceInitialize = true;
        runComputation();
    }

    void ComputeTask::RunComputation()
    {
        _IsForceInitialize = false;
        runComputation();
    }

    void ComputeTask::runComputation()
    {
        if (AppRes::FvMesh == nullptr)
        {
            LxConsole::Error("无网格");
            return;
        }
        MultiThreads::RunHostTask(
            [this]()
            { hostTask(); });
    }

    void ComputeTask::hostTask()
    {
        do
        {
            //1.初始化
            IReset::ResetTypes resetType = IReset::ResetTypes::None;
            if (_IsForceInitialize)
            {
                resetType = IReset::ResetTypes::ClearFields;
            }
            else if (ComputeState::IsSettingChanged())
            {
                resetType = IReset::ResetTypes::UpdateSolveCenter;
            }
            AppRes::StepsCenter->Reset(resetType);
            AppRes::MonitorCenter->Reset(resetType);
            AppRes::SolveCenter->Reset(resetType);
            if (_IsForceInitialize || ComputeState::IsSettingChanged())
            {
                ComputeState::ReportSettingNoticed();
                AppRes::FvMesh->CreateFields();
                AppRes::SolveCenter->InitializeFields(_IsForceInitialize);
            }
            if (_IsForceInitialize)
                return;
            if (ComputeState::IsNeedInterrupt())
                return;
            if (ComputeState::IsSettingChanged())
                continue;
            //2.进入计算
            if (!AppRes::SolveCenter->IsTransient)
            {
                run_steadyCal();
            }
            else
            {
                if (AppRes::SolveCenter->TransientTime->IsImplicit)
                {
                    run_transientImplicit();
                }
                else
                {
                    run_transientExplicit();
                }
            }
            if (ComputeState::IsNeedInterrupt())
                return;
        } while (ComputeState::IsSettingChanged());
        AppRes::ExcuteCenter->ExcuteAfterAll();
    }

    void ComputeTask::run_steadyCal()
    {
        do
        {
            AppRes::SolveCenter->Solve_Steady();
            AppRes::StepsCenter->MoveNextStep_Steady();
            AppRes::MonitorCenter->Monitor_Steady();
            if (ComputeState::IsNeedInterrupt() || ComputeState::IsSettingChanged())
                return;
        } while (AppRes::StepsCenter->SteadyStep.IsContinue());
    }

    void ComputeTask::run_transientExplicit()
    {
        do
        {
            AppRes::SolveCenter->Solve_TransientExplicit();
            moveNext_transient();
            if (ComputeState::IsNeedInterrupt() || ComputeState::IsSettingChanged())
                return;
        } while (AppRes::StepsCenter->TransientStep.IsContinue());
    }

    void ComputeTask::run_transientImplicit()
    {
        do
        {
            do
            {
                AppRes::SolveCenter->Solve_TransientImplicit();
                AppRes::StepsCenter->MoveNextStep_Steady();
                AppRes::MonitorCenter->Monitor_Steady();
                if (ComputeState::IsNeedInterrupt() || ComputeState::IsSettingChanged())
                    return;
            } while (AppRes::StepsCenter->SteadyStep.IsContinue());
            moveNext_transient();
            if (ComputeState::IsNeedInterrupt() || ComputeState::IsSettingChanged())
                return;
        } while (AppRes::StepsCenter->TransientStep.IsContinue());
    }

    void ComputeTask::moveNext_transient()
    {
        AppRes::StepsCenter->MoveNextStep_Transient();
        AppRes::SolveCenter->TransientTime->MoveNextTimeStep();
        AppRes::SolveCenter->SaveOldValue();
        AppRes::MonitorCenter->Monitor_Transient();
    }

}