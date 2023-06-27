#include "PISOUnit.h"

namespace LxCFD
{
    void PISOUnit::Solve_Steady()
    {
        //SIMPLE部分
        SIMPLEUnit::Solve_Steady();
        //PRIME部分
        for (int i1 = 0; i1 < MaxPISOSteps; i1++)
        {
            updateMomentMatrix();
            MultiThreads::RunCalTasks([&](int taskIndex)
                                      {
                                          for (auto &pc : PCors)
                                          {
                                              pc->CalDc_ADiagNotRelaxed(taskIndex);
                                          }
                                      });
            SolveExplicit(Us, Connects);
            SolveExplicit(Vs, Connects);
            SolveExplicit(Ws, Connects);

            updatePCors();
            solvePCors();
            //4.进行修正
            MultiThreads::RunCalTasks([&](int taskIndex)
                                      {
                                          for (auto &pc : PCors)
                                          {
                                              pc->ApplyPCorToUVWP_NoRelax(taskIndex);
                                          }
                                      });
            MultiThreads::RunCalTasks([&](int taskIndex)
                                      {
                                          for (auto &v : Vels)
                                          {
                                              v->CalMassImbalance(taskIndex);
                                          }
                                      });
            updatePressure();
        }
    }
    void PISOUnit::Solve_ImplicitTransient()
    {
        SIMPLEUnit::Solve_ImplicitTransient();
        for (int i1 = 0; i1 < MaxPISOSteps; ++i1)
        {
            updateMomentMatrix();
            MultiThreads::RunCalTasks([&](int taskIndex)
                                      {
                                          for (auto &v : Vels)
                                          {
                                              v->U->TransData->SetAb_ImplicitTrans(taskIndex);
                                              v->V->TransData->SetAb_ImplicitTrans(taskIndex);
                                              v->W->TransData->SetAb_ImplicitTrans(taskIndex);
                                          }
                                      });
            MultiThreads::RunCalTasks([&](int taskIndex)
                                      {
                                          for (auto &pc : PCors)
                                          {
                                              pc->CalDc_ADiagNotRelaxed(taskIndex);
                                          }
                                      });
            SolveExplicit(Us, Connects);
            SolveExplicit(Vs, Connects);
            SolveExplicit(Ws, Connects);

            updatePCors();
            solvePCors();
            //4.进行修正
            MultiThreads::RunCalTasks([&](int taskIndex)
                                      {
                                          for (auto &pc : PCors)
                                          {
                                              pc->ApplyPCorToUVWP_NoRelax(taskIndex);
                                          }
                                      });
            MultiThreads::RunCalTasks([&](int taskIndex)
                                      {
                                          for (auto &v : Vels)
                                          {
                                              v->CalMassImbalance(taskIndex);
                                          }
                                      });
            updatePressure();
        }
    }

}