#pragma once
#include "GeomAverageMonitor.h"
namespace LxCFD
{
    class TestMonitor : public GeomAverageMonitor
    {
    public:
        TestMonitor();
        virtual void RunMonitor() override;
    };
}