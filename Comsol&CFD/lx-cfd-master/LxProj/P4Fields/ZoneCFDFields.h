#pragma once
#include <memory>
#include "Value1Base.h"
#include "PhysicalModel.h"
#include "PossionEquation.h"
#include "NSEquation.h"
#include "ScalarTypes.h"
#include "PressureCorrection.h"
namespace LxCFD
{
    class FvZone;
    class ZoneCFDFields
    {
    public:
        std::shared_ptr<Value1Base<double>> Density = nullptr;
        std::unique_ptr<EquationBase> T = nullptr;
        std::unique_ptr<VelocityVector> Velocity;
        std::unique_ptr<PressureCorrectionBasic> PCor;
        std::unique_ptr<PressureSIMPLE> P;
        void CheckCreate(FvZone *zone);
        void CheckCreate_T();
        void SetParameter_T();
        void CheckCreate_Vel();
        void SetParameter_Vel();
        std::vector<double> *GetArray(ScalarTypes scalarTypes) const;

    protected:
        FvZone *Zone = nullptr;
        PhysicalModel *PhysicalModel = nullptr;
        MaterialData *Material = nullptr;
    };
}