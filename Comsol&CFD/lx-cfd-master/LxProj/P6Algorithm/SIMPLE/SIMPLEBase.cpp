#include "SIMPLEBase.h"

namespace LxCFD
{

    void SIMPLEBase::CreateUnit(std::vector<PressureCorrectionBasic *> &scalars, std::vector<ConnectBase *> &connects, SolverTypes solverType)
    {
        PCors = scalars;
        for (auto pc : PCors)
        {
            Vels.push_back(pc->VelocityVector);
            Us.push_back(pc->VelocityVector->U.get());
            Vs.push_back(pc->VelocityVector->V.get());
            Ws.push_back(pc->VelocityVector->W.get());
            Ps.push_back(pc->PressureSIMPLE);
        }
        Connects = connects;
        SolverType = solverType;
        SetAMGSolver(scalars, connects);
        setReferencePressure();
    }
    void SIMPLEBase::Solve_Steady()
    {
        updateMomentMatrix();
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &pc : PCors)
                                      {
                                          pc->CalDc_ADiagNotRelaxed(taskIndex);
                                      }
                                  });
        RelaxAndSolve(Us, Connects);
        RelaxAndSolve(Vs, Connects);
        RelaxAndSolve(Ws, Connects);
        updatePCors();
        solvePCors();
        //4.进行修正
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &pc : PCors)
                                      {
                                          pc->ApplyPCorToUVWP(taskIndex);
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
        //其他场
    }

    void SIMPLEBase::Solve_ImplicitTransient()
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
        RelaxAndSolve(Us, Connects);
        RelaxAndSolve(Vs, Connects);
        RelaxAndSolve(Ws, Connects);
        updatePCors();
        solvePCors();
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &pc : PCors)
                                      {
                                          pc->ApplyPCorToUVWP(taskIndex);
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
    void SIMPLEBase::SaveOldValue()
    {
        for (auto &v : Vels)
        {
            v->U->TransData->PrepareToSave();
            v->V->TransData->PrepareToSave();
            v->W->TransData->PrepareToSave();
            v->TransVelData->PrepareToSave();
        }
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &v : Vels)
                                      {
                                          v->U->TransData->SaveOldValue(taskIndex);
                                          v->V->TransData->SaveOldValue(taskIndex);
                                          v->W->TransData->SaveOldValue(taskIndex);
                                          v->TransVelData->SaveOldValue(taskIndex);
                                      }
                                  });
    }

    void SIMPLEBase::Solve_ExplicitTransient()
    {
        throw LxTool::GetNotImplementedException();
    }

    void SIMPLEBase::setReferencePressure()
    {
        isExistPressureReference = false;
        for (auto &v : Vels)
        {
            if (v->PressureInOuts.size() > 0)
            {
                isExistPressureReference = true;
            }
        }
        if (!isExistPressureReference)
        {
            Vector3d centerCal;
            double totalVolumn = 0;
            for (auto &p : Ps)
            {
                centerCal += p->Zone->Volumn * p->Center;
                totalVolumn += p->Zone->Volumn;
            }
            centerCal *= (1 / totalVolumn);
            double minlenthSquare = std::numeric_limits<double>::max(); // double.MaxValue;
            for (std::size_t i1 = 0; i1 < Ps.size(); i1++)
            {
                double ls = (Ps.at(i1)->Center - centerCal).CalLengthSquared();
                if (ls < minlenthSquare)
                {
                    minlenthSquare = ls;
                    CenterZoneIndex = i1;
                }
            }
        }
    }

    void SIMPLEBase::updateMomentMatrix()
    {
        //1.求解动量方程
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &v : Vels)
                                      {
                                          v->SetUVW_x(taskIndex);
                                      }
                                  });
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &v : Vels)
                                      {
                                          v->U->CalGradient(taskIndex);
                                          v->V->CalGradient(taskIndex);
                                          v->W->CalGradient(taskIndex);
                                      }
                                  });
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &v : Vels)
                                      {
                                          v->U->SetAb_Step1(taskIndex);
                                          v->V->SetAb_Step1(taskIndex);
                                          v->W->SetAb_Step1(taskIndex);
                                          v->AddViscositySource_LoopFace(taskIndex);
                                      }
                                  });
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &v : Vels)
                                      {
                                          v->U->SetAb_Step2(taskIndex);
                                          v->V->SetAb_Step2(taskIndex);
                                          v->W->SetAb_Step2(taskIndex);
                                          v->AddSource_LoopCell(taskIndex); //每个线程的区域是固定的，不会相互干涉
                                      }
                                  });
    }

    void SIMPLEBase::updatePCors()
    {
        //2.Rhie-Chow求解massImbalance
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &v : Vels)
                                      {
                                          v->CalFaceMassFlux(taskIndex);
                                      }
                                  });
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &v : Vels)
                                      {
                                          v->CalMassImbalance(taskIndex);
                                      }
                                  });
        //3.求解压力修正
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &pc : PCors)
                                      {
                                          pc->Set_x_Bound(taskIndex);
                                      }
                                  });
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &pc : PCors)
                                      {
                                          pc->SetAb_Step1(taskIndex);
                                      }
                                  });
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &pc : PCors)
                                      {
                                          pc->SetAb_Step2(taskIndex);
                                      }
                                  });
    }

    void SIMPLEBase::updatePressure()
    {
        //5.压力场,流场更新
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &p : Ps)
                                      {
                                          p->Predict_bound(taskIndex);
                                      }
                                  });
        if (!isExistPressureReference)
        {
            MultiThreads::RunCalTasks([&](int taskIndex)
                                      {
                                          for (auto &p : Ps)
                                          {
                                              p->CalPressureArea(taskIndex);
                                          }
                                      });
            {
                double iniPA = 0, boundArea = 0;
                for (auto &z : Ps)
                {
                    iniPA += z->InitiialPressureProductBoundArea;
                    boundArea += z->BoundArea;
                }
                double currentPressureProductArea, sum2, sum3;
                ThreadsMath::GetSum(currentPressureProductArea, sum2, sum3);
                PressureReferenceCorrection = (iniPA - currentPressureProductArea) / boundArea;
            }
            MultiThreads::RunCalTasks([&](int taskIndex)
                                      {
                                          for (auto &p : Ps)
                                          {
                                              p->CorrectPressureByReferenct(PressureReferenceCorrection, taskIndex);
                                          }
                                      });
        }
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &p : Ps)
                                      {
                                          p->CalGradient(taskIndex);
                                      }
                                  });
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &v : Vels)
                                      {
                                          v->CalResidual(taskIndex);
                                          v->U->CalResidual(taskIndex);
                                          v->V->CalResidual(taskIndex);
                                          v->W->CalResidual(taskIndex);
                                      }
                                  });
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &v : Vels)
                                      {
                                          v->UpdateUVWBound(taskIndex);
                                      }
                                  });
    }

    void SIMPLEBase::solvePCors()
    {
        if (!isExistPressureReference)
        {
            PCors.at(CenterZoneIndex)->SetAb_PCor0Point(Ps.at(CenterZoneIndex)->CenterCellIndex);
        }
        RelaxAndSolve(PCors, Connects);
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &pc : PCors)
                                      {
                                          pc->Update_x_Bound(taskIndex);
                                      }
                                  });
        MultiThreads::RunCalTasks([&](int taskIndex)
                                  {
                                      for (auto &pc : PCors)
                                      {
                                          pc->CalGradient(taskIndex);
                                      }
                                  });
    }

}