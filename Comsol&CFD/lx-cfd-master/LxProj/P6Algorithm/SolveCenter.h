#pragma once
#include "IReset.h"
#include "ConnectivityAnalysis.h"
#include "TypicalEquationGroup.h"
#include "InitializationGroup.h"
#include "TransientTimeBase.h"
#include "SIMPLEGroup.h"
namespace LxCFD
{
    class SolveCenter : public IReset
    {
    public:
        bool IsTransient;
        std::unique_ptr<TransientTimeBase> TransientTime;
        InitializationGroup InitializeGroup;
        TypicalEquationGroup TemperatureGroup;
        SIMPLEGroup SIMPLEGroup;
        virtual void Reset(ResetTypes resetType) override;
        void InitializeFields(bool isForce);
        void Solve_Steady();
        void Solve_TransientImplicit();
        void Solve_TransientExplicit();
        void SaveOldValue();
    };
}