#pragma once
#include <vector>
#include "LinearSolver.h"
#include "ISolvableUnit.h"
#include "PressureCorrectionBasic.h"
namespace LxCFD
{
    class SIMPLEBase : public LinearSolver, public ISolvableUnit
    {
    public:
        std::vector<VelocityVector *> Vels;
        std::vector<NSEquation *> Us;
        std::vector<NSEquation *> Vs;
        std::vector<NSEquation *> Ws;
        std::vector<PressureCorrectionBasic *> PCors;
        std::vector<PressureSIMPLE *> Ps;
        std::vector<ConnectBase *> Connects; //暂时不用，占位

        bool isExistPressureReference;
        double PressureReferenceCorrection;
        int CenterZoneIndex;

        void CreateUnit(std::vector<PressureCorrectionBasic *> &scalars, std::vector<ConnectBase *> &connects, SolverTypes solverType);
        virtual void Solve_Steady() override;
        virtual void Solve_ImplicitTransient() override;
        virtual void SaveOldValue() override;
        virtual void Solve_ExplicitTransient() override;

    protected:
        void setReferencePressure();
        void updateMomentMatrix();
        void updatePCors();
        void updatePressure();
        virtual void solvePCors();
    };
}