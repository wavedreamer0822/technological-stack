#include "FvMesh.h"
#include <sstream>
#include "AppRes.h"
#include "MGMeshCreator.h"
namespace LxCFD
{
    void FvMesh::PrepareMeshData()
    {
        LxConsole::Info("开始准备网格数据……");
        ReMarkID();
        for (auto &z : Zones)
        {
            z->PrepareMeshData();
        }
        for (auto &c : Contacts)
        {
            c->PrepareMeshData();
        }
        {
            LxConsole::Info("完成网格数据准备。");
            //输出信息
            std::stringstream stream;
            for (auto &z : Zones)
            {
                stream.str("");
                stream << "zone(" << z->Name << ",total IDs(" << z->TotalIndex.ToString() << "),inner IDs(" << z->InnerIndex.ToString() << "))";
                LxConsole::Info(stream.str());
                for (auto &t : z->BoundThreads)
                {
                    stream.str("");
                    stream << "thread(" << t->Name << ",IDs(" << t->ThreadIndex.ToString() << "))";
                    LxConsole::Info(stream.str());
                }
            }
        }
        LxConsole::Info("开始创建多重网格……");
        CreateAMGSolver();
        CreateBiCGSolver();
        LxConsole::Info("完成创建多重网格");
    }
    void FvMesh::ReMarkID()
    {
        int i = 0;
        for (auto &z : Zones)
        {
            z->ID = i;
            ++i;
            int j = 0;
            for (auto &t : z->BoundThreads)
            {
                t->ID = j;
                ++j;
            }
        }
        i = 0;
        for (auto &c : Contacts)
        {
            c->ID = i;
            ++i;
        }
    }
    void FvMesh::Reset(ResetTypes resetType)
    {
    }
    void FvMesh::CreateFields()
    {
        AppRes::SolveCenter->IsTransient = IsTransient;
        if (IsTransient)
        {
            AppRes::SolveCenter->TransientTime = std::move(TransientTimeSetting->GetCopy());
        }
        for (auto &z : Zones)
        {
            z->CFDFields.CheckCreate(z.get());
        }
        for (auto &c : Contacts)
        {
            c->CFDFields.SetParameter(c.get());
        }
    }
    void FvMesh::CreateAMGSolver()
    {

        if (Zones.size() <= 0)
            return;
        MGMeshCreator mgmaker;
        mgmaker.Create(LinearSolverSetting.MaxCoarseLevel, LinearSolverSetting.AMGGroupCount, Zones.at(0)->Cells.size());
        for (auto &z : Zones)
        {
            z->AMGSolver.Create(mgmaker, z.get(), z->Cells.size(), &z->CellCommonArray);
        }
        for (auto &c : Contacts)
        {
            c->AMGSolver.Create(c.get(), mgmaker, c->OZone->AMGSolver, c->NZone->AMGSolver,
                                c->OThread->ID, c->NThread->ID);
        }
    }
    void FvMesh::CreateBiCGSolver()
    {
        //创建BiCGStab
        for (auto &z : Zones)
        {
            z->BiCGSolver.CreateCommon(&z->CellCommonArray, &z->FaceCommonArray);
            z->AMGSolver.BiCGSolver = &z->BiCGSolver;
        }
        for (auto &c : Contacts)
        {
            c->AMGSolver.O_BiCGSolver = c->O_BiCGSolver = &c->OZone->BiCGSolver;
            c->AMGSolver.N_BiCGSolver = c->N_BiCGSolver = &c->NZone->BiCGSolver;
        }
        if (LinearSolverSetting.IsBiCGOnlySupprotAMG)
        {
            for (auto &z : Zones)
            {
                z->BiCGSolver.CreateLocal(z->AMGSolver);
            }
        }
        else
        {
            for (auto &z : Zones)
            {
                z->BiCGSolver.CreateLocal(*z);
            }
        }
    }
}