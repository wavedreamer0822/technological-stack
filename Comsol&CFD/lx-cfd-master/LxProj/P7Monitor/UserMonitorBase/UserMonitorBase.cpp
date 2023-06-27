#include "UserMonitorBase.h"
#include "MultiThreads.h"
#include "AppRes.h"
namespace LxCFD
{
    void UserMonitorBase::RunStatistic()
    {
        if (IsCellValue)
        {
            MultiThreads::RunCalTasks([this](int i)
                                      { FindCellValue(i); });
        }
        else
        {
            MultiThreads::RunCalTasks([this](int i)
                                      { FindFaceValue(i); });
        }
    }
    void UserMonitorBase::FindFaceValue(int taskIndex)
    {
        for (auto &z : AppRes::FvMesh->Zones)
        {
            for (auto &f : z->BoundThreads)
            {
                if (f->MonitorSelector.at(ID))
                {
                    auto *array = z->CFDFields.GetArray(ScalarType);
                    if (array == nullptr)
                        break;
                    CalFaceValue(*z, *f, *array, taskIndex);
                    SetIsCurrentExistTrue(taskIndex);
                }
            }
        }
    }

    void UserMonitorBase::FindCellValue(int taskIndex)
    {
        for (auto &z : AppRes::FvMesh->Zones)
        {
            if (z->MonitorSelector.at(ID))
            {
                auto *array = z->CFDFields.GetArray(ScalarType);
                if (array == nullptr)
                    continue;
                CalCellValue(*z, *array, taskIndex);
                SetIsCurrentExistTrue(taskIndex);
            }
        }
    }

    void UserMonitorBase::SetIsCurrentExistTrue(int taskIndex)
    {
        if (taskIndex == 0 && !IsCurrentExist)
            IsCurrentExist = true;
    }
}