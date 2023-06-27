#include "SolveCenter.h"
#include "TypicalEquationGroup.h"
#include "AppRes.h"
namespace LxCFD
{
    void SolveCenter::Reset(ResetTypes resetType)
    {
        if (resetType == IReset::ResetTypes::None)
            return;
        IsTransient = false;
        TransientTime = nullptr;
        TemperatureGroup.Clear();
    }
    void SolveCenter::InitializeFields(bool isForce)
    {
        if (IsTransient)
        {
            AppRes::SolveCenter->TransientTime->Initialize();
        }
        //重新分组
        ConnectivityAnalysis ca;
        ca.LoadMeshInf(*AppRes::FvMesh);

        // WallDistanceGroup.Rearrange(ca);
        TemperatureGroup.Rearrange(ca);
        SIMPLEGroup.Rearrange(ca);
        // TurbulenceGroup.Rearrange(ca);
        //初始化场
        // foreach (var g in AppRes.SolveCenter.WallDistanceGroup.Units)
        // {
        //     g.Initialize(isForce);
        // }
        InitializeGroup.Initialize(isForce);
    }
    void SolveCenter::Solve_Steady()
    {
        // MultiThreads::RunCalTasks(TurbulenceGroup.UpdateGammaForMomentum);
        SIMPLEGroup.Solve_Steady();
        // TurbulenceGroup.Solve_Steady();
        //MultiThreads.RunCalTasks(TurbulenceGroup.UpdateGammaForTemperature);
        TemperatureGroup.Solve_Steady();
    }
    void SolveCenter::Solve_TransientImplicit()
    {
        // MultiThreads.RunCalTasks(TurbulenceGroup.UpdateGammaForMomentum);
        SIMPLEGroup.Solve_ImplicitTransient();
        // TurbulenceGroup.Solve_ImplicitTransient();
        // MultiThreads.RunCalTasks(TurbulenceGroup.UpdateGammaForTemperature);
        TemperatureGroup.Solve_ImplicitTransient();
    }
    void SolveCenter::Solve_TransientExplicit()
    {
        TemperatureGroup.Solve_ExplicitTransient();
    }
    void SolveCenter::SaveOldValue()
    {
        TemperatureGroup.SaveOldValue();
    }
}