#include "TestMonitor.h"
#include "AppRes.h"
namespace LxCFD
{
    TestMonitor::TestMonitor()
    {
        ScalarType = ScalarTypes::Temperature;
    }

    void TestMonitor::RunMonitor()
    {
        for (auto &z : AppRes::FvMesh->Zones)
        {
            std::vector<double> *array = z->CFDFields.GetArray(ScalarType);
            if (array == nullptr)
                continue;
            std::stringstream ss;
            ss.precision(7);
            ss << "zone:" << z->Name;
            for (auto &f : z->BoundThreads)
            {
                MultiThreads::RunCalTasks(
                    [&,this](int taskIndex)
                    {
                        CalFaceValue(*z, *f, *array, taskIndex);
                    });
                double sum1, sum2, sum3;
                ThreadsMath::GetSum(sum1, sum2, sum3);
                ss << "  " << f->Name << ":" << sum1 / sum2;
            }
            LxConsole::Calc(ss.str());
        }
    }
}