#pragma once
#include <vector>
#include "Value1Base.h"
#include "Vector3d.h"
namespace LxCFD
{
    class FvZone;
    class BoussinesqSource :public Value1Base<Vector3d>
    {
    public:
        double RefT;
        std::vector<double> *ScalarT;
        Vector3d Total;
        BoussinesqSource(double RefT, double ThermExpanCoeff, double RefDensity, Vector3d &Gravity, FvZone &zone);
        virtual Vector3d GetCellValue(int cellIndex) override;
    };
}