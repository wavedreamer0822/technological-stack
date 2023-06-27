#pragma once
#include "LinearSolverBase.h"
#include "SolverTypes.h"
#include "FvZone.h"
#include "FvContact.h"
namespace LxCFD
{
    class LinearSolver : public LinearSolverBase
    {
    public:
        SolverTypes SolverType = SolverTypes::AMGV;
        void SetAMGSolver(std::vector<AMGInZone *> &AMGsInZone, std::vector<AMGInContact *> &AMGsInContact);
        template <typename T1, typename T2>
        void SetAMGSolver(std::vector<T1 *> &provideZone, std::vector<T2 *> &provideContact)
        {
            for (auto &z : provideZone)
            {
                addAMGSolver(&z->Zone->AMGSolver);
            }
            for (auto &c : provideContact)
            {
                addAMGSolver(&c->Contact->AMGSolver);
            }
        }
        template <typename T1, typename T2>
        void RelaxAndSolve(std::vector<T1 *> &equations, std::vector<T2 *> &connects)
        {
            MultiThreads::RunCalTasks([&](int taskIndex)
                                     {
                                         for (auto &e : equations)
                                         {
                                             e->Relax(taskIndex);
                                         }
                                     });
            switch (SolverType)
            {
            case SolverTypes::AMGV:
                SolveByJacobi(equations, connects);
                LinkAMG(equations, connects);
                AMG_V(connects); //VÑ­»·
                SolveByJacobi(equations, connects);
                break;
            case SolverTypes::AMGF:
                SolveByJacobi(equations, connects);
                LinkAMG(equations, connects);
                AMG_F(connects); //FÑ­»·
                SolveByJacobi(equations, connects);
                break;
            case SolverTypes::Jacobi:
                SolveByJacobi(equations, connects);
                break;
            case SolverTypes::BiCGSTAB:
                throw LxTool::GetNotImplementedException();
            }
        }
        template <typename T1, typename T2>
        void RelaxAndSolve(std::vector<T1 *> &scalars, std::vector<T2 *> &connects, SolverTypes solverTypes)
        {
            SolverType = solverTypes;
            RelaxAndSolve(scalars, connects);
        }
        template <typename T1, typename T2>
        void SolveExplicit(std::vector<T1 *> &scalars, std::vector<T2 *> &connects)
        {
            MultiThreads::RunCalTasks([&](int taskIndex)
                                      {
                                          for (auto &c : connects)
                                          {
                                              c->Copy_xArray(taskIndex);
                                          }
                                      });
            MultiThreads::RunCalTasks([&](int taskIndex)
                                      {
                                          for (auto &s : scalars)
                                          {
                                              s->CalByExplicit_Step1(taskIndex);
                                          }
                                      });
            MultiThreads::RunCalTasks([&](int taskIndex)
                                     {
                                         for (auto &s : scalars)
                                         {
                                             s->CalByExplicit_Step2(taskIndex);
                                         }
                                     });
        }

    private:
        void addAMGSolver(AMGInZone *AMG);
        void addAMGSolver(AMGInContact *amg);
    };
}