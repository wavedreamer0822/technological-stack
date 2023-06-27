#include "SIMPLEUnit.h"

namespace LxCFD
{
    void SIMPLEUnit::solvePCors()
    {
        SIMPLEBase::solvePCors();
        for (int i1 = 0; i1 < MaxNonOrthCorSteps; i1++)
        {
            MultiThreads::RunCalTasks([&](int taskIndex)
                                      {
                                          for (auto &pc : PCors)
                                          {
                                              pc->Setb_Step1_Cor(taskIndex);
                                          }
                                      });
            MultiThreads::RunCalTasks([&](int taskIndex)
                                      {
                                          for (auto &pc : PCors)
                                          {
                                              pc->Setb_Step2_Cor(taskIndex);
                                          }
                                      });
            SIMPLEBase::solvePCors();
        }
    }
}