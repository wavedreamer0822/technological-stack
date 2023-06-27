#pragma once
#include "GroupBase.h"
#include "ConnectivityAnalysis.h"
namespace LxCFD
{
    template <typename T>
    class UnitGroupBase : public GroupBase
    {
    public:
        std::vector<std::unique_ptr<T>> Units;
        virtual void Clear() override
        {
            Units.clear();
        }
        virtual void Rearrange(ConnectivityAnalysis &connectivityAnalysis) = 0;
    };
}