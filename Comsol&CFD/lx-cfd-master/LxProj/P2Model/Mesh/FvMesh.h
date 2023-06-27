#pragma once
#include <memory>
#include "FvZone.h"
#include "FvContact.h"
#include "TransientTimeFixed.h"
#include "IReset.h"
namespace LxCFD
{
    class FvMesh : public IPrepareMesh, public IReset
    {
    public:
        class LinearSolverSetup
        {
        public:
            int AMGGroupCount = 4;
            int MaxCoarseLevel = 50;
            bool IsBiCGOnlySupprotAMG = true;
        };
        std::vector<std::unique_ptr<FvZone>> Zones;
        std::vector<std::unique_ptr<FvContact>> Contacts;
        bool IsTransient = false;
        std::unique_ptr<TransientTimeBase> TransientTimeSetting = std::unique_ptr<TransientTimeFixed>(new TransientTimeFixed());
        LinearSolverSetup LinearSolverSetting;

        virtual void PrepareMeshData() override;
        virtual void Reset(ResetTypes resetType) override;
        void ReMarkID();
        void CreateFields();
        void CreateAMGSolver();
        void CreateBiCGSolver();
    };
}