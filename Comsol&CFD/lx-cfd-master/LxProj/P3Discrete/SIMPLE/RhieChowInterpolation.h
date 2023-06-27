#pragma once
#include <vector>
#include "Vector3d.h"
#include "FvFace.h"

namespace LxCFD
{
    class PressureCorrectionBasic;
    class PressureSIMPLE;
    class RhieChowInterpolation
    {
    public:
        void SetParameter(PressureCorrectionBasic *pressureCorInSIMPLE, PressureSIMPLE *pressureInSIMPLE);
        virtual Vector3d CalVelocityCorrection_Inner(int faceID, FvFace &face);
        virtual Vector3d CalVelocityCorrection_Bound(int faceID, FvFace &face);

    protected:
        std::vector<Vector3d> *Dc;
        std::vector<double> *Pressure;
        std::vector<Vector3d> *PressureGrad;
    };
}