#pragma once
#include "MonitorBase.h"
#include "ScalarTypes.h"
#include "FvZone.h"
#include "ThreadsMath.h"
namespace LxCFD
{
    class UserMonitorBase : public MonitorBase
    {
    public:
        ScalarTypes ScalarType;
        bool IsCellValue;
        void RunStatistic();
        void FindFaceValue(int taskIndex);
        virtual void CalFaceValue(FvZone &selectedZone, FvThread &selectedThread, std::vector<double> &scalarArray, int taskIndex) = 0;
        void FindCellValue(int taskIndex);
        virtual void CalCellValue(FvZone &selectedZone, std::vector<double> &scalarArray, int taskIndex) = 0;
        void SetIsCurrentExistTrue(int taskIndex);
    };
}