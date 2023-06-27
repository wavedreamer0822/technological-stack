#include "TypicalEquationUnit.h"

namespace LxCFD
{
    void TypicalEquationUnit::CreateUnit(std::vector<EquationBase *> &scalars, std::vector<ConnectBase *> &connects, SolverTypes solverTypes)
    {
        Equations = scalars;
        Connects = connects;
        SetAMGSolver(scalars, connects);
        SolverType = solverTypes;
    }
    void TypicalEquationUnit::SaveOldValue()
    {
        for (auto &s : Equations)
        {
            s->TransData->PrepareToSave();
        }
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &s : Equations)
                                      {
                                          s->TransData->SaveOldValue(taskIndex);
                                      }
                                  });
    }
    void TypicalEquationUnit::Solve_Steady()
    {
        prepareMatirx();
        RelaxAndSolve(Equations, Connects);
        updateBounds();
    }
    void TypicalEquationUnit::Solve_ExplicitTransient()
    {
        prepareMatirx();
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &s : Equations)
                                      {
                                          s->TransData->SetAb_ExplicitTrans(taskIndex);
                                      }
                                  });
        SolveExplicit(Equations, Connects);
        updateBounds();
    }
    void TypicalEquationUnit::Solve_ImplicitTransient()
    {
        prepareMatirx();
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &s : Equations)
                                      {
                                          s->TransData->SetAb_ImplicitTrans(taskIndex);
                                      }
                                  });
        RelaxAndSolve(Equations, Connects);
        updateBounds();
    }
    void TypicalEquationUnit::prepareMatirx()
    {
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &s : Equations)
                                      {
                                          s->Set_x_Bound(taskIndex);
                                      }
                                  });
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &s : Equations)
                                      {
                                          s->CalGradient(taskIndex);
                                      }
                                  });
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &s : Equations)
                                      {
                                          s->SetAb_Step1(taskIndex);
                                      }
                                      for (auto &c : Connects)
                                      {
                                          c->SetAb_Step1(taskIndex);
                                      }
                                  });
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &s : Equations)
                                      {
                                          s->SetAb_Step2(taskIndex);
                                      }
                                  });
    }
    void TypicalEquationUnit::updateBounds()
    {
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &c : Connects)
                                      {
                                          c->Copy_xArray(taskIndex);
                                      }
                                  });
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &s : Equations)
                                      {
                                          s->CalResidual(taskIndex);
                                      }
                                  });
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &s : Equations)
                                      {
                                          s->Update_x_Bound(taskIndex);
                                      }
                                      for (auto &c : Connects)
                                      {
                                          c->Update_x_Bound(taskIndex);
                                      }
                                  });
    }
}